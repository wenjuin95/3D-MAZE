/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:27:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/17 13:51:41 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief draw the square in the minimap
 * @param data get the image, minimap texture size, x, y and color
 * @param x x coordinate of the square
 * @param y y coordinate of the square
 * @param color color of the square
*/
void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->minimap.texture_size)
	{
		j = 0;
		while (j < data->minimap.texture_size)
		{
			color_pixel_put(&data->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief draw the minimap line by line
 * @param data get the minimap map
 * @param x x coordinate of the minimap
 * @param y y coordinate of the minimap
 * @note 1. if the minimap map is player, draw the square with player color
 * @note 2. if the minimap map is wall, draw the square with wall color
 * @note 3. if the minimap map is floor, draw the square with floor color
 * @note 4. if the minimap map is space, draw the square with space color
*/
void	draw_line(t_data *data, int x, int y)
{
	if (data->minimap.map[y][x] == 'P')
		draw_square(data, x * data->minimap.texture_size,
			y * data->minimap.texture_size, MAP_COLOR_PLAYER);
	if (data->minimap.map[y][x] == '1')
		draw_square(data, x * data->minimap.texture_size,
			y * data->minimap.texture_size, MAP_COLOR_WALL);
	if (data->minimap.map[y][x] == '0')
		draw_square(data, x * data->minimap.texture_size,
			y * data->minimap.texture_size, MAP_COLOR_FLOOR);
	if (data->minimap.map[y][x] == ' ')
		draw_square(data, x * data->minimap.texture_size,
			y * data->minimap.texture_size, MAP_COLOR_SPACE);

}

/**
 * @brief draw the minimap
 * @param data get the minimap map
 * @note 1. draw the minimap line by line
 * @note 2. if the minimap map is empty, break the loop
*/
void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap.size)
	{
		x = 0;
		while (x < data->minimap.size)
		{
			if (!data->minimap.map[y] || !data->minimap.map[y][x]
				|| data->minimap.map[y][x] == '\0')
				break;
			draw_line(data, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief render the minimap
 * @param data get the mlx, window, image, minimap, and player position
 * @note 1. initialize the image for the minimap
 * @note 2. draw the minimap
 * @note 3. put the image to the window
 * @note 4. destroy the image for overlap minimap when player move
*/
void	render_minimap(t_data *data)
{
	int	img_size;

	img_size = MAP_PIXEL;
	initialize_image(data, &data->img, img_size, img_size);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img,
		data->minimap.texture_size, data->minimap.texture_size);
	mlx_destroy_image(data->mlx, data->img.img);
}
