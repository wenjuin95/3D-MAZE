/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:54:16 by welow             #+#    #+#             */
/*   Updated: 2024/12/13 11:26:22 by welow            ###   ########.fr       */
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
	int		*texture_buffer;
	int		x;
	int		y;

	if (path == NULL)
		clean_and_exit(data);
	get_xpm_data(data, path);
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
			++x;
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

/**
 * @brief determines which texture to use based on the direction the ray is
 *		  coming from and which side of the wall was hit.
 * @param data the data to be calculated
 * @param ray the ray to be calculated
 * @note 1. if the ray hit a vertical wall
 * @note	a. if the ray is moving to the left
 * @note		i. set the texture index to west
 * @note	b. if the ray is moving to the right
 * @note		i. set the texture index to east
*/
void	get_texture_index(t_data *data, t_raycast *ray)
{
	if (ray->side == VERTICAL_WALL)
	{
		if (ray->dir_x < 0)
			data->texture.texture_index = WEST;
		else
			data->texture.texture_index = EAST;
	}
	else
	{
		if (ray->dir_y < 0)
			data->texture.texture_index = NORTH;
		else
			data->texture.texture_index = SOUTH;
	}
}

/**
 * @brief update the texture pixel based on raycast result
 * @param data the data to be calculated
 * @param tex the texture to be calculated
 * @param ray the ray to be calculated
 * @param x the x coordinate of the screen width
 * @note 1. calculate the x coordinate on the texture
 * @note	a. if the ray hit horizontal wall or the ray hit vertical wall
 * @note		i. calculate the x-coordinate on the texture based on the
 * 				   wall hit position
 * @note 2. calculate how much to increase the texture coordinate per screen
 * 			pixel
 * @note	a. calculate the step size for the texture
 * @note 3. initialize the texture position for the first pixel to be drawn
 * @note 4. initialize the y-coordinate to the starting point of the line to
 * 			be drawn
 * @note	a. loop through and calculate the y-coordinate on the texture
 * @note 5. if the ray hit horizontal wall
 * @note	a. darken the color for the horizontal wall
 * @note 6. set each pixel color on the screen
*/
void	update_texture_pixel(t_data *data, t_tex *tex, t_raycast *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);
	tex->tex_x = (int)(ray->wall_x * tex->texture_size);
	if ((ray->side == VERTICAL_WALL && ray->dir_x < 0)
		|| (ray->side == HORIZONTAL_WALL && ray->dir_y > 0))
		tex->tex_x = tex->texture_size - tex->tex_x - 1;
	tex->step = 1.0 * tex->texture_size / ray->line_height;
	tex->position = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->tex_y = (int)tex->position & (tex->texture_size - 1);
		tex->position += tex->step;
		color = data->tex_data[tex->texture_index][tex->texture_size
			* tex->tex_y + tex->tex_x];
		if (ray->side == HORIZONTAL_WALL)
			color = (color >> 1) & 8355711;
		data->tex_pixel[y][x] = color;
		y++;
	}
}
