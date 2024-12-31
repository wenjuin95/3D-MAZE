/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:23:38 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 12:51:51 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * error handling to check is it the map is closed by wall
 * flood fill will start when there is a space in the map
 */
int	check_enclosed_space(char **map, int rows)
{
	char	**temp_map;

	temp_map = duplicate_map(map, rows);
	if (temp_map == NULL)
		return (1);
	if (flood_fill(temp_map, rows) == 1)
	{
		free_array((void **)temp_map);
		return (1);
	}
	free_array((void **)temp_map);
	return (0);
}

int	flood_fill(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				flood_fill_recursive(map, i, j, height);
			j++;
		}
		i++;
	}
	return (0);
}

void	flood_fill_recursive(char **map, int i, int j, int height)
{
	if (i < 0 || i >= height || j < 0 || j >= (int)ft_strlen(map[i])
		|| map[i][j] == '1')
		return ;
	if (map[i][j] == ' ')
	{
		map[i][j] = 'X';
		flood_fill_recursive(map, i + 1, j, height);
		flood_fill_recursive(map, i - 1, j, height);
		flood_fill_recursive(map, i, j + 1, height);
		flood_fill_recursive(map, i, j - 1, height);
	}
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == '\0')
		return ;
}

int	get_width(t_map *map)
{
	int	i;
	int	j;

	if (!map->map || map->map[0] == NULL)
		return (ft_error("Invalid ument structure"), 1);
	i = ft_strlen(map->map[0]);
	j = 0;
	while (++j < map->map_height)
	{
		if (i < ft_strlen(map->map[j]))
			i = ft_strlen(map->map[j]);
	}
	return (i);
}

/**
 * check is file can be open
 */
int	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_error("Fail to open texture file"), exit(1));
	return (0);
}
