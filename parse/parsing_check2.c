/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:11:43 by chtan             #+#    #+#             */
/*   Updated: 2024/12/30 21:01:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:28:25 by nchok             #+#    #+#             */
/*   Updated: 2024/12/18 17:18:20 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void check_map(t_data *data)
{
	if (data->map.map_height < 3)
	{
		clean_and_exit(data);
		ft_error("blah"), exit(1);
	}
	if (check_enclosed_space(data->map.map, data->map.map_height) == 1)
	{
		clean_and_exit(data);
		ft_error("blah"), exit(1);
	}
	replace_space_to_1(data->map.map, data->map.map_height);
	if (check_map_details(data) == 1)
		ft_error("blah"), clean_and_exit(data), exit(1);
}

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
