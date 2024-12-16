/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_dda.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:28:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/16 13:52:13 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief calculate the ray direction and delta distance
 * @param x the x coordinate of the screen width
 * @param ray the ray to be calculated
 * @param player the player to be calculated
 * @note 1. calculate the ray position and direction
 * @note 2. calculate the length of ray form current position to
 * 			"next x or y side"
*/
void	initialize_ray(int x, t_raycast *ray, t_player *player)
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
void	initialize_dda(t_raycast *ray, t_player *player)
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
 * @note 2. if next grid crossing in y is closer than x
 * @note 	a. move the ray to the next y-side
 * @note 	b. update the map y coordinate
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
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
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
 * @note 1. get the distance between the intersection
 * 			of the ray and the camera plane with the wall
 * @note 2. get the line height to draw
 * @note 3. get the start and end point to draw
 * @note 4. calculate the wall_x which is the exact position of the wall
 * 			hit by the ray and set the texture x coordinate to the wall_x
 * @note 5. "floor" is to ensure the texture coord are accurate and display
 * 			the texture correctly
*/
void	calculate_line_height_to_draw(t_raycast *ray, t_data *data,
		t_player *player)
{
	if (ray->side == 0)
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
	if (ray->side == 0)
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
		initialize_ray(x, &data->ray, player);
		initialize_dda(&data->ray, player);
		perform_dda(data, &data->ray);
		calculate_line_height_to_draw(&data->ray, data, player);
		update_texture_pixel(data, &data->texture, &data->ray, x);
		x++;
	}
	return (0);
}
