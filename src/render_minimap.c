/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:27:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/13 11:22:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//void	draw_square(t_data *data, int x, int y, int color)
//{
//	int	i;
//	int	j;

//	i = 0;
//	while (i < data->minimap.texture_size)
//	{
//		j = 0;
//		while (j < data->minimap.texture_size)
//		{
//			set_color_to_pixel(&data->img, x + j, i + y, color);
//			j++;
//		}
//		i++;
//	}
//}

//void	draw_line(t_data *data, int x, int y)
//{
//	if (data->minimap.map[y][x] == 'P')
//		draw_square(data, x * data->minimap.texture_size,
//			y * data->minimap.texture_size, MAP_COLOR_PLAYER);
//	if (data->minimap.map[y][x] == '1')
//		draw_square(data, x * data->minimap.texture_size,
//			y * data->minimap.texture_size, MAP_COLOR_WALL);
//	if (data->minimap.map[y][x] == '0')
//		draw_square(data, x * data->minimap.texture_size,
//			y * data->minimap.texture_size, MAP_COLOR_FLOOR);
//	if (data->minimap.map[y][x] == ' ')
//		draw_square(data, x * data->minimap.texture_size,
//			y * data->minimap.texture_size, MAP_COLOR_SPACE);

//}

//void	draw_minimap(t_data *data)
//{
//	int	x;
//	int	y;

//	y = 0;
//	while (y < data->minimap.size)
//	{
//		x = 0;
//		while (x < data->minimap.size)
//		{
//			if (!data->minimap.map[y] || !data->minimap.map[y][x]
//				|| data->minimap.map[y][x] == '\0')
//				break;
//			draw_line(data, x, y);
//			x++;
//		}
//		y++;
//	}
//}

//void	render_minimap(t_data *data)
//{
//	int	img_size;

//	img_size = MAP_PIXEL; //minimap width / height
//	initialize_image(data, &data->img, img_size, img_size);
//	draw_minimap(data);
//	mlx_put_image_to_window(data->mlx, data->win, data->img.img,
//		data->minimap.texture_size, data->minimap.texture_size);
//	mlx_destroy_image(data->mlx, data->img.img);
//}
