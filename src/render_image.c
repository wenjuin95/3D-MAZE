/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:09:40 by welow             #+#    #+#             */
/*   Updated: 2024/12/06 22:20:09 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief set color to each pixel in the image
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
static void	set_color_to_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->img_addr[pixel] = color;
}

/**
 * @brief after set color to each pixel then set the image to each position
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
static void	set_image(t_data *data, t_img *img, int x, int y)
{
	if (data->tex_pixel[y][x] > 0)
		set_color_to_pixel(img, x, y, data->tex_pixel[y][x]);
	else if (y < data->win_height / 2)
		set_color_to_pixel(img, x, y, data->texture.hex_ceiling);
	else if (y < data->win_height - 1)
		set_color_to_pixel(img, x, y, data->texture.hex_floor);
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
			set_image(data, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
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

	if (data->tex_pixel != NULL)
		free_array((void **)data->tex_pixel);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAP_COLOR_PLAYER 0x00FF00 // Green
#define MAP_COLOR_WALL 0x000000 // black
#define MAP_COLOR_FLOOR 0xE6E6E6 // Light Gray
#define MAP_COLOR_SPACE 0x000000 // black

char	*add_minimap_line(t_data *data, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(data->minimap_size + 1, sizeof * line);
	if (line == NULL)
		return (NULL);
	x = 0;
	while (x < data->minimap_size && x < data->map_width)
	{
		if ((int)data->player.pos_x == (x + data->minimap_offset_x)
			&& (int)data->player.pos_y == (y + data->minimap_offset_y))
		{
			line[x] = 'P';
		}
		else if (data->map[y + data->minimap_offset_y][x + data->minimap_offset_x] == '1')
			line[x] = '1';
		else if (data->map[y + data->minimap_offset_y][x + data->minimap_offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

char	**get_minimap(t_data *data)
{
	char	**map;
	int		y;

	map = ft_calloc(data->minimap_size + 1, sizeof * map);
	if (map == NULL)
		return (NULL);
	y = 0;
	while (y < data->minimap_size && y < data->map_height)
	{
		map[y] = add_minimap_line(data, y);
		if (map[y] == NULL)
		{
			free_array((void **)map);
			return (NULL);
		}
		y++;
	}
	return (map);
}

int	get_map_offset(t_data *data, int size, int pos)
{
	if (pos > data->minimap_view_distance
		&& size - pos > data->minimap_view_distance + 1)
		return (pos - data->minimap_view_distance);
	if (pos > data->minimap_view_distance
		&& size - pos <= data->minimap_view_distance + 1)
		return (size - data->minimap_size);
	return (0);
}

void	set_minimap_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->minimap_texture_size)
	{
		j = 0;
		while (j < data->minimap_texture_size)
		{
			set_color_to_pixel(&data->img, x + j, i + y, color);
			j++;
		}
		i++;
	}	
}

void	draw_minimap_tile(t_data *data, int x, int y)
{
	if (data->minimap_map[y][x] == 'P')
		set_minimap_pixel(data, x * data->minimap_texture_size,
			y * data->minimap_texture_size, MAP_COLOR_PLAYER);
	if (data->minimap_map[y][x] == '1')
		set_minimap_pixel(data, x * data->minimap_texture_size,
			y * data->minimap_texture_size, MAP_COLOR_WALL);
	if (data->minimap_map[y][x] == '0')
		set_minimap_pixel(data, x * data->minimap_texture_size,
			y * data->minimap_texture_size, MAP_COLOR_FLOOR);
	if (data->minimap_map[y][x] == ' ')
		set_minimap_pixel(data, x * data->minimap_texture_size,
			y * data->minimap_texture_size, MAP_COLOR_SPACE);

}

void	set_minimap_border(t_data *data, int color)
{
	int	size;
	int	x;
	int	y;

	size = MAP_PIXEL + data->minimap_texture_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_color_to_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap_size)
	{
		x = 0;
		while (x < data->minimap_size)
		{
			if (!data->minimap_map[y] || !data->minimap_map[y][x] 
				|| data->minimap_map[y][x] == '\0')
				break;
			draw_minimap_tile(data, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border(data, MAP_COLOR_SPACE);
}

void	render_minimap(t_data *data)
{
	int	img_size;

	img_size = MAP_PIXEL + data->minimap_texture_size;
	initialize_image(data, &data->img, img_size, img_size);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img,
		data->minimap_texture_size, data->minimap_texture_size);
	mlx_destroy_image(data->mlx, data->img.img);
}

void	put_minimap(t_data *data)
{
	data->minimap_view_distance = MAP_VIEW;
	data->minimap_size = (2 * data->minimap_view_distance) + 1;
	data->minimap_texture_size = MAP_PIXEL / (2 * data->minimap_view_distance);
	// data->minimap_offset_x = get_map_offset(data, data->map_width, (int)data->player.pos_x);
	// data->minimap_offset_y = get_map_offset(data, data->map_height, (int)data->player.pos_y);
	data->minimap_offset_x = 0;
	data->minimap_offset_y = 0;
	data->minimap_map = get_minimap(data);
	if (data->minimap_map == NULL)
		return ;
	render_minimap(data);
	free_array((void **)data->minimap_map);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		put_minimap(data);
}
