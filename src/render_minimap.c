/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:27:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 13:58:53 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
			set_color_to_pixel(&data->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

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

// void	set_minimap_border(t_data *data, int color)
// {
// 	int	size;
// 	int	x;
// 	int	y;

// 	size = MAP_PIXEL + data->minimap.texture_size;
// 	y = 0;
// 	while (y < size)
// 	{
// 		x = 0;
// 		while (x <= size)
// 		{
// 			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
// 				set_color_to_pixel(&data->img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
	// set_minimap_border(data, MAP_COLOR_SPACE);
}

void	render_minimap(t_data *data)
{
	//int	img_size;

	//img_size = MAP_PIXEL + data->minimap.texture_size; //minimap width / height
	int img_height = MAP_PIXEL + data->minimap.texture_size;
	int img_width = MAP_PIXEL + data->minimap.texture_size;
	printf("img_height: %d\n", img_height);
	printf("img_width: %d\n", img_width);
	initialize_image(data, &data->img, img_width, img_height);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img,
		data->minimap.texture_size, data->minimap.texture_size);
	mlx_destroy_image(data->mlx, data->img.img);
}
