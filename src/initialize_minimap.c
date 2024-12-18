/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:24:23 by welow             #+#    #+#             */
/*   Updated: 2024/12/17 13:47:40 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief check each line of the minimap and give the value
 * @param data get the player position, minimap visible x and y
 * @param x x coordinate visible in the minimap
 * @param y y coordinate visible in the minimap
*/
char	initialize_line(t_data *data, int x, int y)
{
	int	minimap_x;
	int	minimap_y;

	minimap_x = x + data->minimap.visible_x;
	minimap_y = y + data->minimap.visible_y;
	if ((int)data->player.pos_x == (minimap_x)
		&& (int)data->player.pos_y == (minimap_y))
		return ('P');
	else if (data->map.map_layout[minimap_y][minimap_x] == '1')
		return ('1');
	else if (data->map.map_layout[minimap_y][minimap_x] == '0')
		return ('0');
	else if (data->map.map_layout[minimap_y][minimap_x] == ' ')
		return (' ');
	else
		return ('\0');
}

/**
 * @brief search what to assign in each minimap line
 * @param data get the minimap size, map width, player position,
 * 			   minimap offset x and y
 * @param y height of the minimap
 * @return the minimap line
 * @note 1. if the player position is same with x and y, assign 'P'
 * 			to the line
*/
char	*add_minimap_line(t_data *data, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(data->minimap.size + 1, sizeof * line);
	if (line == NULL)
		return (NULL);
	x = 0;
	while (x < data->minimap.size)
	{
		line[x] = initialize_line(data, x, y);
		x++;
	}
	return (line);
}

/**
 * @brief get the map for the minimap
 * @param data get the minimap size and map height
 * @return the minimap map
 * @note 1. The function allocates memory for the minimap map.
 * @note 2. The function then iterates through the minimap size and map
 * 			height to add each line of the minimap to the map.
*/
char	**get_minimap(t_data *data)
{
	char	**map;
	int		y;

	map = ft_calloc(data->minimap.size + 1, sizeof * map);
	if (map == NULL)
		return (NULL);
	y = 0;
	while (y < data->minimap.size)
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

/**
 * @brief calculate the visible part of the map in player's position
 * @param data get the minimap view distance and minimap size
 * @param size get the size of the map
 * @param pos get the position of the player
 * @return the visible part of the map in player's position
 * @note 1. if the player is center of the map
 * @note	a. visible portion will be center around the player
 * @note 2. if the player is near to the end of the map
 * @note	a. visible portion start potion will be furthe away
 * 			   from the end of the map
 * @note 3. if the player is near to the start of the map
 * @note	a. visible portion will be very begininng of the map
*/
int	get_visible_map(t_data *data, int size, int pos)
{
	if (pos > data->minimap.view_distance
		&& size - pos > data->minimap.view_distance)
	{
		return (pos - data->minimap.view_distance);
	}
	if (size - pos <= data->minimap.view_distance)
	{
		return (size - data->minimap.size);
	}
	return (0);
}

/**
 * @brief put minimap to the window
 * @param data get minimap_view_distance, minimap_size, minimap_texture_size,
 * 			   minimap_offset_x, minimap_offset_y and minimap_map
 * @note 1. get the length how far for player to up, down, left and right to
 * 			the end of the minimap
 * @note 2. get the size of the minimap
 * @note 3. get the image size for the minimap
 * @note 4. get the visible part of the map in player's position in x-axis
 * @note 5. get the visible part of the map in player's position in y-axis
 * @note 6. get the minimap map
*/
void	put_minimap(t_data *data)
{
	data->minimap.view_distance = MAP_VIEW;
	data->minimap.size = (2 * data->minimap.view_distance);
	data->minimap.texture_size = MAP_PIXEL / data->minimap.size;
	data->minimap.visible_x = get_visible_map(data,
		data->map.map_width, (int)data->player.pos_x);
	data->minimap.visible_y = get_visible_map(data,
		data->map.maply_height, (int)data->player.pos_y);
	data->minimap.map = get_minimap(data);
	if (data->minimap.map == NULL)
		return ;
	// debug_map(&data->minimap); //debug the minimap
	render_minimap(data);
	free_array((void **)data->minimap.map);
}
