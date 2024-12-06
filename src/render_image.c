/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:09:40 by welow             #+#    #+#             */
/*   Updated: 2024/12/06 18:51:33 by welow            ###   ########.fr       */
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

void	render_minimap(t_data *data, t_minimap *minimap)
{
	int	img_size;

	img_size = 8 + minimap->texture_size;
	initialize_image(data, &data->img, img_size, )
}

char	*add_minimap_line(t_data *data, t_minimap *minimap, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(minimap->minimap_size + 1, sizeof * line);
	if (line == NULL)
		return (NULL);
	x = 0;
	while (x < minimap->minimap_size && x < data->map_width)
	{
		if ((int)data->player.pos_x == (x + minimap->offset_x)
			&& (int)data->player.pos_y == (y + minimap->offset_y))
			line[x] = 'P';
		else if (data->map[y + minimap->offset_y][x + minimap->offset_x] == '1')
			line[x] = '1';
		else if (data->map[y + minimap->offset_y][x + minimap->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

char	**generate_minimap(t_data *data, t_minimap *minimap)
{
	char	**map;
	int		y;

	map = ft_calloc(minimap->minimap_size + 1, sizeof * map);
	if (map == NULL)
		return (NULL);
	y = 0;
	while (y < minimap->minimap_size && y < data->map_height)
	{
		map[y] = add_minimap_line(data, minimap, y);
		if (map[y] == NULL)
		{
			free_array((void **)map);
			return (NULL);
		}
		y++;
	}
	return (map);
}

int	get_map_offset(t_minimap *minimap, int map_size, int player_pos)
{
	if (player_pos > minimap->view_distance && map_size - player_pos > minimap->view_distance + 1)
		return (player_pos - minimap->view_distance);
	if (player_pos > minimap->view_distance && map_size - player_pos <= minimap->view_distance + 1)
		return (map_size - minimap->minimap_size);
	return (0);
}


void	open_map(t_data *data)
{
	t_minimap	minimap;

	minimap.img = &data->img;
	minimap.view_distance = 5;
	minimap.minimap_size = 128 / (2 * minimap.view_distance);
	minimap.offset_x = get_map_offset(&data->minimap, data->map_width, (int)data->player.pos_x);
	minimap.offset_y = get_map_offset(&data->minimap, data->map_height, (int)data->player.pos_y);
	minimap.map = generate_minimap(data, &minimap);
	render_minimap(data, &minimap);
	free_array((void **)minimap.map);
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
	{
		//mlx_string_put(data->mlx, data->win, data->win_width / 2 - 50,
		//	data->win_height / 2 - 10, 0x00FF0000, "YOU ARE ON THE MAP");
		open_map(data);
	}
}
