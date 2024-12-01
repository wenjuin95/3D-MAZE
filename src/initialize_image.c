/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:54:16 by welow             #+#    #+#             */
/*   Updated: 2024/12/01 00:10:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief convert xpm to image
 * @param data the data to be initialized
 * @param path the path to the xpm file
*/
static void	convert_xpm_to_img(t_data *data, char *path)
{
	//initialize the texture to 0
	// data->img.img = NULL;
	// data->img.img_addr = NULL;
	// data->img.pixel_bits = 0;
	// data->img.size_line = 0;
	// data->img.endian = 0;
	//////////////////////////
	data->img.img = mlx_xpm_file_to_image(data->mlx, path,
			&data->texture.texture_size, &data->texture.texture_size);
	if (data->img.img == NULL)
		clean_and_exit(data);
	data->img.img_addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.pixel_bits, &data->img.size_line, &data->img.endian);
}

/**
 * @brief take the converted xpm image and assign it to each pointer buffer
 * @param data the data to be converted
 * @param path the path to the xpm file
 * @return int* the buffer of the image for each texture
 * @note 1. purpose for create another (xpm_to_img) function is to
 * 			copy the different buffer to each texture buffer
 * 			like NORTH, SOUTH, WEST, EAST
*/
static int	*xpm_to_img(t_data *data, char *path)
{
	int		*texture_buffer;
	int		x;
	int		y;

	convert_xpm_to_img(data, path);
	texture_buffer = ft_calloc(1, sizeof * texture_buffer
			* data->texture.texture_size * data->texture.texture_size);
	if (texture_buffer == NULL)
		clean_and_exit(data);
	y = 0;
	while (y < data->texture.texture_size)
	{
		x = 0;
		while (x < data->texture.texture_size)
		{
			texture_buffer[y * data->texture.texture_size + x]
				= data->img.img_addr[y * data->texture.texture_size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, data->img.img);
	return (texture_buffer);
}

/**
 * @brief initialize the image data to each array of texture
 * @param data the north, south, west, and east texture
 * @return void
 * @note 1. allocate 4 memory for the texture
*/
void	initialize_img(t_data *data)
{
	data->tex_data = ft_calloc(4, sizeof * data->tex_data);
	if (data->tex_data == NULL)
		clean_and_exit(data);
	data->tex_data[NORTH] = xpm_to_img(data, data->texture.north);
	data->tex_data[SOUTH] = xpm_to_img(data, data->texture.south);
	data->tex_data[WEST] = xpm_to_img(data, data->texture.west);
	data->tex_data[EAST] = xpm_to_img(data, data->texture.east);
}
