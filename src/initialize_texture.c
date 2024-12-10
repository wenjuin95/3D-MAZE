/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:54:16 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 10:58:01 by welow            ###   ########.fr       */
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
 * @brief determines which texture to use based on the direction the ray is coming from and which
 * 		  side of the wall was hit.
 * @param data the data to be calculated
 * @param ray the ray to be calculated
*/
void	get_texture_index(t_data *data, t_raycast *ray)
{
	if (ray->side == 0) //if the ray hit vertical wall
	{
		if (ray->dir_x < 0)//if the ray is moving to the left
			data->texture.texture_index = WEST; //set the texture index to west
		else //if the ray is moving to the right
			data->texture.texture_index = EAST; //set the texture index to east
	}
	else // if the ray hit horizontal wall
	{
		if (ray->dir_y < 0) //if the ray is moving down
			data->texture.texture_index = NORTH; //set the texture index to north
		else
			data->texture.texture_index = SOUTH; //set the texture index to south
	}
}
/**
 * @brief update the texture pixel based on raycast result
 * @param data the data to be calculated
 * @param tex the texture to be calculated
 * @param ray the ray to be calculated
 * @param x the x coordinate of the screen width
*/
void	update_texture_pixel(t_data *data, t_tex *tex, t_raycast *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);
	//x coordinate on the texture
	tex->tex_x = (int)(ray->wall_x * tex->texture_size); //Calculates the x-coordinate on the texture based on the wall hit position (ray->wall_x) and the texture size
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0)) //Checks if the texture needs to be flipped horizontally.
		tex->tex_x = tex->texture_size - tex->tex_x - 1; //Flips the texture coordinate if necessary.

	//calculate how much to increase the texture coordinate per screen pixel
	tex->step = 1.0 * tex->texture_size / ray->line_height; //Calculates the step size for sampling the texture vertically

	//start texture position
	tex->position = (ray->draw_start - data->win_height / 2 //Initializes the texture position for the first pixel to be drawn.
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start; //Initializes the y-coordinate to the starting point of the line to be drawn.
	while (y < ray->draw_end)
	{
		//typecast the position to integer and mask with (texture_size - 1) to wrap around the texture if it exceeds the texture size
		tex->tex_y = (int)tex->position & (tex->texture_size - 1); //Calculates the y-coordinate on the texture.
		tex->position += tex->step; //Advances the texture position by the step size.
		color = data->tex_data[tex->texture_index][tex->texture_size
			* tex->tex_y + tex->tex_x]; //Retrieves the color from the texture at the calculated coordinates

		if (ray->side == 1) //if the ray hit horizontal wall
			color = (color >> 1) & 8355711; //Darker the color for the horizontal wall

		//if (color > 0) //Checks if the color is not transparent.
			data->tex_pixel[y][x] = color;  //set the pixel color on the screen.
		y++; //Advances to the next y-coordinate.
	}
}
