/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:09:40 by welow             #+#    #+#             */
/*   Updated: 2025/01/14 12:16:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief pixel put the color to the image
 * @param img get the image struct
 * @param x get the x coordinate
 * @param y get the y coordinate
 * @param color get the color
 * @note 1. "img->size_line / 4" is convert the size_line to pixel
 * @note 2. "y * (img->size_line / 4)" is to get total pixel in y axis
 * @note 3. "+ x" is to get the final pixel
 * @note 4. "y * (img->size_line / 4) + x" mean index of the pixel
 * @note 5. "img->img_addr[pixel] = color" is to set the pixel to the color
*/
void	color_pixel_put(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	//printf("%d\n", pixel);
	img->img_addr[pixel] = color;
}

/**
 * @brief set image or color according the position of the window
 * @param data get teture_pixel, win_height, win_width and hex_ceiling
 * 			   and hex_floor
 * @param img get the image struct
 * @param x get the x coordinate
 * @param y get the y coordinate
 * @note 1. if the texture pixel coordinate is not 0 then set the image
 * @note 2. if the y is less than half of the window height then set
 * 			the color ceiling
 * @note 3. if the y is less than the window height then set the color floor
*/
static void	set_image(t_data *data, t_img *img, int x, int y)
{
	if (data->texture.pixel[y][x] != 0)
		color_pixel_put(img, x, y, data->texture.pixel[y][x]);
	else if (y < data->win_height / 2)
		color_pixel_put(img, x, y, data->map.ceiling_hex);
	else if (y < data->win_height - 1)
		color_pixel_put(img, x, y, data->map.floor_hex);
}

/**
 * @brief put image to the window
 * @param data get win_height, win_width, mlx and win
 * @note 1. initialize the image
 * @note 2. loop through the window height and width and set the pixel
 * @note 3. put the image to the window
 * @note 4. "mlx_destroy_image" is to prevent memory leak after put
 * 			the image
*/
void	put_image(t_data *data)
{
	//t_img	img;
	int		x;
	int		y;

	//initialize_image(data, &img, data->win_width, data->win_height);
	//data->img = img;
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_image(data, &data->img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

/**
 * @brief initialize the map size for texture
 * @param data get the texture pixel
 * @note 1. if the texture pixel is not null then free the texture pixel
 * 			to prevent memory overlaping
*/
void	init_map_size_for_texture(t_data *data)
{
	int	i;

	if (data->texture.pixel != NULL)
		free_array((void **)data->texture.pixel);
	data->texture.pixel = ft_calloc(data->win_height + 1, sizeof
			* data->texture.pixel);
	if (data->texture.pixel == NULL)
		clean_and_exit(data);
	i = 0;
	while (i < data->win_height)
	{
		data->texture.pixel[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture.pixel);
		if (data->texture.pixel[i] == NULL)
			clean_and_exit(data);
		i++;
	}
}

/**
 * @brief render the image
 * @param data data struct
*/
void	render_the_image(t_data *data)
{
	init_map_size_for_texture(data);
	raycasting(&data->player, data);
	put_image(data);
	if (data->on_map == 1)
	{
		render_minimap(data);
		mlx_mouse_hide(data->mlx, data->win);
	}
	else
		mlx_mouse_show(data->mlx, data->win);
}
