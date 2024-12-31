/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:11:43 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 10:35:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * make sure all the rgb values are valid between 0 and 255
 */
int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_error("Invalid RGB value"), 1);
		i++;
	}
	return (0);
}

/**
 * just change all the space to 1
 */
static void replace_space_to_1(char **map, int map_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

// int	check_surrounding(char **map, int i, int j, int max_h)
// {
// 	int			row;
// 	int			result;
// 	t_map_info	info;

// 	info.map = map;
// 	info.max_h = max_h;
// 	row = i - 1;
// 	while (row <= i + 1 && row < max_h)
// 	{
// 		if (row < 0 || !map[row])
// 		{
// 			row++;
// 			continue ;
// 		}
// 		info.max_w = (int)ft_strlen(map[row]);
// 		result = process_row(&info, i, j, row);
// 		if (result == FAILURE)
// 			return (FAILURE);
// 		row++;
// 	}
// 	return (SUCCESS);
// }

int	scan_map(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && i <= height)
	{
		j = 0;
		while (map[i][j] && j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == 'X')
			{
				// if (check_surrounding(map, i, j, height) == 1)
				// 	return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * first the map row should biigger or equal to the 3
 * then flood filll to check is it the map is closed by wall
 */
void check_map(t_data *data)
{
	if (data->map.map_height < 3)
		ft_error("hello!"), clean_and_exit(data);
	if (check_enclosed_space(data->map.map, data->map.map_height) == 1)
		ft_error("hello world!!"), clean_and_exit(data);
	replace_space_to_1(data->map.map, data->map.map_height);
	if (check_map_details(data) == 1)
		ft_error("blah"), clean_and_exit(data);
}

/**
 * check is it the map is closed by wall again
 * check is it the map has valid element and only one player
 */
int	check_map_details(t_data *data)
{
	if (check_map_closed(data->map.map, data->map.map_height) == 1)
		ft_error("Map not surrounded by wall"), clean_and_exit(data), exit(1);
	if (check_num_players(data->map.map) == 1)
	{
		clean_and_exit(data);
		ft_error("This is a single player game"), exit(1);
	}
	check_valid_element(data);
	return (0);
}
