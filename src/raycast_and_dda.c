/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_dda.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:28:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/13 00:03:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief calculate the ray direction and delta distance
 * @param x the x coordinate of the screen width
 * @param ray the ray to be calculated
 * @param player the player to be calculated
 * @note 1. calculate the ray direction
 * @note 	a. calculate the camera plane x coordinate
 * @note	b. calculate the direction x and y of the ray
 * @note 2. calculate the length of ray from "x or y side" to
 * 			"next x or y side"
 * 			a. calculate the delta distance x and y
*/
void	calculate_ray_and_grid(int x, t_raycast *ray, t_player *player)
{
	ray->camera = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/**
 * @brief calculate the step and initialize side distance
 * @param ray the ray to be calculated
 * @param player the player to be calculated
 * @note 1. if the ray is facing left direction in x axis
 * @note 	a. ray move to the left
 * @note 	b. calculate the initial side distance in the x-direction
 * @note 2. if the ray is facing right direction in x axis
 * @note 	a. ray move to the right
 * @note 	b. calculate the initial side distance in the x-direction
 * @note 3. if the ray is facing down direction in y axis
 * @note 	a. ray move down
 * @note 	b. calculate the initial side distance in the y-direction
 * @note 4. if the ray is facing up direction in y axis
 * @note 	a. ray move up
 * @note 	b. calculate the initial side distance in the y-direction
*/
void	set_dda(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

/**
 * @brief perform DDA algorithm
 * @param data the data to be calculated
 * @param ray the ray to be calculated
 * @note 1. if next grid crossing in x is closer than y
 * @note 	a. move the ray to the next x-side
 * @note 	b. update the map x coordinate
 * @note 	c. set the side to vertical wall
 * @note 2. if next grid crossing in y is closer than x
 * @note 	a. move the ray to the next y-side
 * @note 	b. update the map y coordinate
 * @note 	c. set the side to horizontal wall
*/
void	perform_dda(t_data *data, t_raycast *ray)
{
	int	hit_wall;

	hit_wall = 0;
	while (hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = VERTICAL_WALL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = HORIZONTAL_WALL;
		}
		if (data->map.map_layout[ray->map_y][ray->map_x] == '1')
			hit_wall = 1;
	}
}

/**
 * @brief calculate the line height to draw
 * @param ray the ray to be calculated
 * @param data the data to be calculated
 * @param player the player to be calculated
 * @note 1. calculate the distance of the perpendicular ray
 * @note	a. if the ray hit a vertical wall
 * @note		i. calculate the perpendicular distance to the wall
 * 				   for a horizontal hit
 * @note	b. if the ray hit a horizontal wall
 * @note		i. calculate the perpendicular distance to the wall
 * 				   for a vertical hit
 * @note 2. calculate the line height to draw on screen
 * @note 3. calculate the starting point to draw the line
 * @note	b. if the starting point is above the window
 * @note		i. set the starting point to the top of the window
 * @note 4. calculate the ending point to draw the line
 * @note	a. if the ending point is below the window
 * @note		i. set the ending point to the bottom of the window
 * @note 5. calculate the value of wall_x
 * @note	a. if the ray hit a horizontal wall
 * @note		i. calculate the x-coordinate of the wall hit
 * @note			for a horizontal hit
 * @note	b. if the ray hit a vertical wall
 * @note		i. calculate the x-coordinate of the wall hit
 * @note			for a vertical hit
 * @note 6. normalize the wall_x and ensure it is between 0 and 1
*/
void	calculate_line_height_to_draw(t_raycast *ray, t_data *data, t_player *player)
{
	if (ray->side == VERTICAL_WALL)
		ray->wall_dis = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dis = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dis);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	(void)player;
	if (ray->side == VERTICAL_WALL)
		ray->wall_x = player->pos_y + ray->wall_dis * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dis * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		calculate_ray_and_grid(x, &data->ray, player);
		set_dda(&data->ray, player);
		perform_dda(data, &data->ray);
		calculate_line_height_to_draw(&data->ray, data, player);
		update_texture_pixel(data, &data->texture, &data->ray, x);
		x++;
	}
	return (0);
}
