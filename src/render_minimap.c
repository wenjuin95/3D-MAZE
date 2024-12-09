/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:27:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/08 23:43:14 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief set the color to the pixel into a square
 * @param data the main data structure
 * @param w size of the square (width)
 * @param h size of the square (height)
 * @param color the color to be set
 * @note 1. "w + j" is total how long of the square (width)
 * @note 2. "i + h" is total how long of the square (height)
*/
void	draw_a_square(t_data *data, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->minimap.texture_size)
	{
		j = 0;
		while (j < data->minimap.texture_size)
		{
			set_color_to_pixel(&data->img, w + j, h + i, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief draw the minimap line by line
 * @param data the main data structure
 * @param w width of the map
 * @param h height of the map
*/
void	draw_line(t_data *data, int w, int h)
{
	if (data->minimap.map[h][w] == 'P')
		draw_a_square(data, w * data->minimap.texture_size,
			h * data->minimap.texture_size, MAP_COLOR_PLAYER);
	if (data->minimap.map[h][w] == '1')
		draw_a_square(data, w * data->minimap.texture_size,
			h * data->minimap.texture_size, MAP_COLOR_WALL);
	if (data->minimap.map[h][w] == '0')
		draw_a_square(data, w * data->minimap.texture_size,
			h * data->minimap.texture_size, MAP_COLOR_FLOOR);
	if (data->minimap.map[h][w] == ' ')
		draw_a_square(data, w * data->minimap.texture_size,
			h * data->minimap.texture_size, MAP_COLOR_SPACE);
}

/**
 * @brief draw the minimap
 * @param data the main data structure
 * @note 1. if the width of the map is empty or
 * 			the map is empty, break
*/
void	draw_minimap(t_data *data)
{
	int	w;
	int	h;

	h = 0;
	while (h < data->minimap.size)
	{
		w = 0;
		while (w < data->minimap.size)
		{
			if (data->minimap.map[h] == NULL
				|| data->minimap.map[h][w] == '\0')
				break ;
			draw_line(data, w, h);
			w++;
		}
		h++;
	}
}
//////////////////////////////////////////////////////////////////////////////
#define PI 3.142
float	set_player_angle(t_data *data)
{
	float	angle;

	if (data->player.dir_x > 0 && data->player.dir_y >= 0)
		angle = atan(data->player.dir_y / data->player.dir_x);
	else if (data->player.dir_x > 0 && data->player.dir_y < 0)
		angle = atan(data->player.dir_y / data->player.dir_x) + 2 * PI;
	else if (data->player.dir_x < 0)
		angle = atan(data->player.dir_y / data->player.dir_x) + PI;
	else if (data->player.dir_x == 0 && data->player.dir_y > 0)
		angle = PI / 2;
	else
		angle = 3 * PI / 2;
	return (angle);
}

void	draw_player_view(t_data *data)
{
	data->player.angle = set_player_angle(data);
	// printf("angle: %f\n", data->player.angle);
	if (data->player.angle - (PI / 2) < 1e-6)
		printf("down\n");
	else if (data->player.angle - (3 * PI / 2) < 1e-6)
		printf("up\n");
	else if (data->player.angle - 0 < 1e-6)
		printf("right\n");
	else if (data->player.angle - (PI) < 1e-6)
		printf("left\n");
}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief render the minimap
 * @param data the main data structure
*/
void	render_minimap(t_data *data)
{
	int	img_size;

	img_size = data->map_width * data->minimap.texture_size;
	initialize_image(data, &data->img, img_size, img_size);
	draw_minimap(data);
	draw_player_view(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img,
		data->minimap.texture_size, data->minimap.texture_size);
	mlx_destroy_image(data->mlx, data->img.img);
}
