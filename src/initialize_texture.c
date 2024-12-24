/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:54:16 by welow             #+#    #+#             */
/*   Updated: 2024/12/24 21:58:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief convert xpm to image and get the data
 * @param data the data to be initialized
 * @param path the path to the xpm file
 * @note 1. mlx_xpm_file_to_image is a function to convert xpm to an image
*/
static void	get_xpm_data(t_data *data, char *path)
{
	data->img.img = mlx_xpm_file_to_image(data->mlx, path,
			&data->texture.texture_size,
			&data->texture.texture_size);
	if (data->img.img == NULL)
		clean_and_exit(data);
	data->img.img_addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.pixel_bits,
			&data->img.size_line,
			&data->img.endian);
}

/**
 * @brief copy the data from the xpm file to the texture buffer
 * @param data the data to be converted
 * @param path the path to the xpm file
 * @return int* the buffer of the image for each texture
 * @note 1. "y * data->texture.texture_size + x" is the formula to get the
 * 			pixel data from the xpm file
 * @note 2. mlx_destroy_image is to free the unused image data
*/
static int	*ft_strdup_data(t_data *data, char *path)
{
	int		*texture_data;
	int		x;
	int		y;

	if (path == NULL)
		clean_and_exit(data);
	get_xpm_data(data, path);
	texture_data = ft_calloc(1, sizeof * texture_data
			* data->texture.texture_size * data->texture.texture_size);
	if (texture_data == NULL)
		clean_and_exit(data);
	y = 0;
	while (y < data->texture.texture_size)
	{
		x = 0;
		while (x < data->texture.texture_size)
		{
			texture_data[y * data->texture.texture_size + x]
				= data->img.img_addr[y * data->texture.texture_size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, data->img.img);
	return (texture_data);
}

/**
 * @brief initialize the image data to each array of texture
 * @param data the north, south, west, and east texture
 * @return void
 * @note 1. allocate 4 + 1(null) memory for the texture data
*/
void	initialize_texture(t_data *data)
{
	data->tex_data = ft_calloc(5, sizeof * data->tex_data);
	if (data->tex_data == NULL)
		clean_and_exit(data);
	data->tex_data[NORTH] = ft_strdup_data(data, data->map.north);
	data->tex_data[SOUTH] = ft_strdup_data(data, data->map.south);
	data->tex_data[WEST] = ft_strdup_data(data, data->map.west);
	data->tex_data[EAST] = ft_strdup_data(data, data->map.east);
}
