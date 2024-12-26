/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:48:19 by welow             #+#    #+#             */
/*   Updated: 2024/12/26 15:00:45 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief draw a square in the minimap
 * @param data get the image container, x and y coordinate and color
 * @param x x coordinate
 * @param y y coordinate
 * @param color color of the square
 * @note 1. loop through the square
 * @note 2. then put the color to the pixel
*/
void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			color_pixel_put(&data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief render the minimap
 * @param data get the map layout and player position
 * @note 1. loop through the map layout
 * @note 2. if the map layout is '1' then draw the wall
 * @note 3. if the map layout is '0' then draw the floor
 * @note 4. if the map layout is 'P' then draw the player
*/
void	render_minimap(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map.map_layout[i])
	{
		j = 0;
		while (data->map.map_layout[i][j])
		{
			if (data->map.map_layout[i][j] == '1')
				draw_square(data, j * MINIMAP_SIZE, i * MINIMAP_SIZE,
					MINIMAP_WALL);
			else if (data->map.map_layout[i][j] == '0')
				draw_square(data, j * MINIMAP_SIZE, i * MINIMAP_SIZE,
					MINIMAP_FLOOR);
			else if (((int)data->player.pos_x == j && (int)data->player.pos_y
					== i)
				|| data->map.map_layout[i][j] == 'P')
				draw_square(data, j * MINIMAP_SIZE, i * MINIMAP_SIZE,
					MINIMAP_PLAYER);
			j++;
		}
		i++;
	}
}

/**
 * @brief put minimap to the window
 * @param data get the image size for the minimap
 * @note 1. make the image container for the minimap
 * @note 2. render the minimap
 * @note 3. put the minimap to the window
 * @note 4. destroy the image container (prevent memory leak)
*/
void	put_minimap(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, data->map.map_width
			* MINIMAP_SIZE, data->map.maply_height * MINIMAP_SIZE);
	data->img.img_addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.pixel_bits,
			&data->img.size_line,
			&data->img.endian);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}
