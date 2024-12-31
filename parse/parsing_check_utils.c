/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:23:38 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 11:58:16 by welow            ###   ########.fr       */
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
	// if (scan_map(map, height) == 1)
	// 	return (1);
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
