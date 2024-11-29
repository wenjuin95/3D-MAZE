/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/29 20:46:54 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_width = SCREEN_W;
	data->win_height = SCREEN_H;
	data->texture.texture_size = TEXTURE_SIZE;
}

void	initialize_square_texture_pixel(t_data *data)
{
	int	i;

	data->tex_pixel = ft_calloc(data->win_height + 1, sizeof * data->tex_pixel);
	if (data->tex_pixel == NULL)
		clean_and_exit(data);
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pixel[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pixel);
		if (data->tex_pixel[i] == NULL)
			clean_and_exit(data);
		i++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief calculate the ray direction and delta distance
 * @param x the x coordinate of the screen width
 * @param ray the ray to be calculated
 * @param player the player to be calculated
 * @note 1. calculate the ray direction from the player to the wall
 * @note 	a. camera_x: calculate how far left or right this ray is from the center of the camera
 * @note 	b. dir_x: calculate the ray direction of x
 * @note 2. calculate the delta distance ( determine the distance the ray has to travel
 * 			to go from one x-side to the next x-side, or one y-side to the next y-side)
 * @note 	a. delta_dist_x: calculate how far the ray moves in the each grid x
*/
void	calculate_ray_and_grid(int x, t_raycast *ray, t_player *player)
{
	ray->camera = 2 * x / (double)SCREEN_W - 1;
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
*/
void	set_dda(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0) //if ray is facing left direction in x axis
	{
		ray->step_x = -1; //ray moves to the left
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x; //calculate the distance to the next grid x
	}
	else //if ray is facing right direction in x axis
	{
		ray->step_x = 1; //ray moves to the right
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) //calculate the distance to the next grid x
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0) //if ray is facing up direction in y axis
	{
		ray->step_y = -1; //ray move up
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else //if ray is facing down direction in y axis
	{
		ray->step_y = 1; //ray move down
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

/**
 * @brief perform DDA algorithm
 * @param data the data to be calculated
 * @param ray the ray to be calculated
 * @note 1. perform DDA algorithm to calculate the distance to the wall
 * @note 	a. if the distance to the next grid x < distance to the next grid y, then
 * 			   move to the next grid x and add the distance to the next grid x
 * @note 	b. if the distance to the next grid y < distance to the next grid x, then
 * 			   move to the next grid y and add the distance to the next grid y
 * @note 	c. if the map is a wall, then hit the wall
*/
void	perform_dda(t_data *data, t_raycast *ray)
{
	int	hit_wall;

	hit_wall = 0;
	while (hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x; //add the distance to the next grid x
			ray->map_x += ray->step_x; //move to the next grid x
			ray->side = 0; //set the side to 0
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y; //add the distance to the next grid y
			ray->map_y += ray->step_y; //move to the next grid y
			ray->side = 1; //set the side to 1
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			hit_wall = 1;
	}
}

void	calculate_line_height(t_raycast *ray, t_data *data, t_player *player)
{
	if (ray->side == 0) //if the side is 0 mean horizontal side
		ray->wall_dis = (ray->side_dist_x - ray->delta_dist_x);
	else //if the side is 1 mean vertical side
		ray->wall_dis = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dis);  //not yet done
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
		calculate_ray_and_grid(x, &data->ray, player);
		set_dda(&data->ray, player);
		perform_dda(&data->ray, data);
		calculate_line_height(&data->ray, data, player); //not yet
		update_texture_pixel(data, &data->texture, &data->ray, x); //not yet
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////

void	render_image(t_data *data)
{
	initialize_square_texture_pixel(data);
	raycasting(&data->player, data); //OTW
	render_frame(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (data.win == NULL)
		return (1);
	initialize_img(&data);
	render_image(&data);
	debuger(&data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_loop(data.mlx);
}
