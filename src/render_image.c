/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:09:40 by welow             #+#    #+#             */
/*   Updated: 2024/11/29 14:14:05 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief initialize the image
 * @param data get mlx pointer
 * @param img get img pointer
 * @param width get the window width
 * @param height get the window height
 * @note 1. initialize all the img struct to 0 to prevent garbage value
 * @note 2. create a new image with mlx_new_image
 * @note 3. use mlx_get_data_addr to get the address of the image
*/
void	initialize_image(t_data *data, t_img *img, int w_width, int w_height)
{
	//initialize to all 0 again
	img->img = NULL;
	img->img_addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
	//////////////////////////
	img->img = mlx_new_image(data->mlx, w_width, w_height);
	if (img->img == NULL)
		clean_and_exit(data);
	img->img_addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->size_line, &img->endian);

}

/**
 * @brief set the image pixel to each coordinate
 * @param img get the image struct
 * @param x get the x coordinate
 * @param y get the y coordinate
 * @param color get the color
 * @note 1. "img->size_line / 4" is convert the size_line to pixel
 * @note 2. "y * (img->size_line / 4)" is to get total pixel in y axis
 * @note 3. "+ x" is to get the final pixel
 * @note 4. "y * (img->size_line / 4) + x" mean beginner of the pixel
 * @note 5. "img->img_addr[pixel] = color" is to set the pixel to the color
*/
static void	set_image_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->img_addr[pixel] = color;
}

/**
 * @brief set the image in each position
 * @param data get teture_pixel, win_height, win_width and hex_ceiling
 * 			   and hex_floor
 * @param img get the image struct
 * @param x get the x coordinate
 * @param y get the y coordinate
 * @note 1. if the texture pixel coordinate is more than 0 then set the image
 * @note 2. if the y is less than half of the window height then set
 * 			the color ceiling
 * @note 3. if the y is less than the window height then set the color floor
*/
static void	set_frame_image_pixel(t_data *data, t_img *img, int x, int y)
{
	if (data->tex_pixel[y][x] > 0)
		set_image_pixel(img, x, y, data->tex_pixel[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(img, x, y, data->texture.hex_ceiling);
	else if (y < data->win_height - 1)
		set_image_pixel(img, x, y, data->texture.hex_floor);
}

/**
 * @brief render the frame
 * @param data get win_height, win_width, mlx and win
 * @note 1. initialize the image
 * @note 2. loop through the window height and width and set the pixel
 * @note 3. put the image to the window
*/
void	render_frame(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	initialize_image(data, &img, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
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

void	render_image(t_data *data)
{
	initialize_square_texture_pixel(data);
	raycasting(&data->player, data);
	render_frame(data);
}
