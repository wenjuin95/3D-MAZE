/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:24:23 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 11:35:45 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief search what to assign in each minimap line
 * @param data get the minimap size, map width, player position,
 * 			   minimap offset x and y
 * @param y height of the minimap
 * @return the minimap line
 * @note 1. if the player position is same with x and y, assign 'P' to the line
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
		if ((int)data->player.pos_x == (x + data->minimap.offset_x)
			&& (int)data->player.pos_y == (y + data->minimap.offset_y))
			line[x] = 'P';
		else if (data->map.map_layout[y + data->minimap.offset_y][x + data->minimap.offset_x] == '1')
			line[x] = '1';
		else if (data->map.map_layout[y + data->minimap.offset_y][x + data->minimap.offset_x] == '0')
			line[x] = '0';
		else if (data->map.map_layout[y + data->minimap.offset_y][x + data->minimap.offset_x] == ' ')
			line[x] = ' ';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

/**
 * @brief get the map for the minimap
 * @param data get the minimap size and map height
 * @return the minimap map
 * @note 1. The function allocates memory for the minimap map.
 * @note 2. The function then iterates through the minimap size and map height to add each
 * 			line of the minimap to the map.
*/
char	**get_minimap(t_data *data)
{
	char	**map;
	int		y;

	map = ft_calloc(data->minimap.size + 1, sizeof * map);
	if (map == NULL)
		return (NULL);
	y = 0;
	while (y < data->minimap.size && y < data->map.maply_height)
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
 * @brief get the map offset
 * @param data get the minimap view distance and minimap size
 * @param size get the size of the map
 * @param pos get the position of the player
 * @return the offset of the map
 * @note 1. The first if statement ensures the minimap is centered around the player when they are not too close to the edges of the map.
 * @note 2. The second if statement ensures the minimap shows the end of the map when the player is near the end.
 * @note 3. If the player is near the start of the map, the minimap starts from the beginning.
*/
int	get_map_offset(t_data *data, int size, int pos)
{
	//Condition: This checks if the player's position (pos) is greater than the minimap_view_distance and if the remaining distance to the end of the map (size - pos) is greater than minimap_view_distance + 1.
	//Meaning for the Player: If the player is far enough from both the start and the end of the map, the minimap will be centered around the player's position. The offset is calculated as pos - minimap_view_distance, which means the minimap will start showing from a point that is minimap_view_distance units before the player's position.
	if (pos > data->minimap.view_distance
		&& size - pos > data->minimap.view_distance + 1)
		return (pos - data->minimap.view_distance);

	//Condition: This checks if the player's position (pos) is greater than the minimap_view_distance and if the remaining distance to the end of the map (size - pos) is less than or equal to minimap_view_distance + 1.
	//Meaning for the Player: If the player is close to the end of the map, the minimap will shift to show the end of the map. The offset is calculated as size - minimap_size, which means the minimap will start showing from a point that ensures the end of the map is visible.
	if (pos > data->minimap.view_distance
		&& size - pos <= data->minimap.view_distance + 1)
		return (size - data->minimap.size);
	return (0);
}

/**
 * @brief put minimap to the window
 * @param data get minimap_view_distance, minimap_size, minimap_texture_size,
 * 			   minimap_offset_x, minimap_offset_y and minimap_map
 * @note 1. get the minimap view distance
 * @note 2. get the minimap size (width and height)
 * @note 3. get the minimap texture size
 * @note 4. get the minimap offset x and y
 * @note 5. get the minimap map
*/
void	put_minimap(t_data *data)
{
	data->minimap.view_distance = MAP_VIEW; //map view distance means how far the map can be seen

	//"2 * data->minimap_view_distance" is to get the width and height of the minimap
	//"+1" is to get the center of the minimap
	data->minimap.size = (2 * data->minimap.view_distance);

	//MAP_PIXEL is the size of the minimap
	//"/ (2 * data->minimap_view_distance)" is to get the size of the minimap texture
	data->minimap.texture_size = MAP_PIXEL / data->minimap.size;

	//get the offset x and y of the minimap
	data->minimap.offset_x = get_map_offset(data, data->map.map_width, (int)data->player.pos_x);
	data->minimap.offset_y = get_map_offset(data, data->map.maply_height, (int)data->player.pos_y);

	//get the minimap map and render the minimap
	data->minimap.map = get_minimap(data);
	if (data->minimap.map == NULL)
		return ;
	 debug_map(&data->minimap); //debug the minimap
	render_minimap(data);
	free_array((void **)data->minimap.map);
}
