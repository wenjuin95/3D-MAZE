/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_dda.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:28:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/27 00:07:36 by welow            ###   ########.fr       */
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
void	get_step(t_raycast *ray, t_player *player)
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
			ray->side = VERTICAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = HORIZONTAL;
		}
		if (data->map.map[ray->map_y][ray->map_x] == '1')
			hit_wall = 1;
	}
}

/**
 * @brief perform raycasting
 * @param player the player to be calculated
 * @param data the data to be calculated
 * @note 1. initialize the ray
 * @note 2. get the step
 * @note 3. perform DDA
 * @note 4. calculate the wall distance according to the side
 * @note 5. update the texture pixel
*/
int	raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		initialize_ray(x, &data->ray, player);
		get_step(&data->ray, player);
		perform_dda(data, &data->ray);
		if (data->ray.side == VERTICAL)
			data->ray.wall_dis = (data->ray.side_dist_x
					- data->ray.delta_dist_x);
		else if (data->ray.side == HORIZONTAL)
			data->ray.wall_dis = (data->ray.side_dist_y
					- data->ray.delta_dist_y);
		update_texture_pixel(data, &data->texture, &data->ray, x);
		x++;
	}
	return (0);
}
