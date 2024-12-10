/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 14:17:30 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east
		|| !map->floor || !map->ceiling || !map->map)
		ft_error("Fail to allocate memory56");
	check_valid_file_name(map->north, ".xpm");
	check_valid_file_name(map->south, ".xpm");
	check_valid_file_name(map->west, ".xpm");
	check_valid_file_name(map->east, ".xpm");
}

/**
 * search for the target in the 2d array
 * the function return (int)
 */
static int	search(char **array, int rows, char *target)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == target[0] && array[i][j + 1] == target[1])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

/**
 * search for the target in the 2d array
 * the function return (size_t)
 */
static size_t	search2(char **array, int row, char *target)
{
	size_t	i;
	size_t	j;
	size_t	rows;

	i = 0;
	rows = (size_t)row;
	while (i < rows)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == target[0] && array[i][j + 1] == target[1])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

static t_map *p_struct(t_map *map)
{
	map->north = remove_nl(ft_substr(map->file[search(map->file, map->file_height,
					"NO")], 3, ft_len(map->file[search2(map->file,
						map->file_height, "NO")])));
	map->south = remove_nl(ft_substr(map->file[search(map->file, map->file_height,
					"SO")], 3, ft_len(map->file[search2(map->file,
						map->file_height, "SO")])));
	map->west = remove_nl(ft_substr(map->file[search(map->file, map->file_height,
					"WE")], 3, ft_len(map->file[search2(map->file,
						map->file_height, "WE")])));
	map->east = remove_nl(ft_substr(map->file[search(map->file, map->file_height,
					"EA")], 3, ft_len(map->file[search2(map->file,
						map->file_height, "EA")])));
	// map->sprite = ft_substr(map->map[search(map->map, map->file_height, "S ")], 2, ft_strlen(map->map[4]));
	map->floor = set_rgb(remove_nl(ft_substr(map->file[search(map->file, map->file_height, "F ")], 2,
					ft_strlen(map->file[search(map->file, map->file_height, "F ")]))));
	map->ceiling = set_rgb(remove_nl(ft_substr(map->file[search(map->file, map->file_height, "C ")], 2,
					ft_strlen(map->file[search(map->file, map->file_height, "C ")]))));
	for (int i = 0; i < map->file_height; i++)
	{
		for (int j = 0; j < ft_strlen(map->file[i]); j++)
		{
			if (map->file[i][j] == '1' && map->file[i][j + 1] == '1' && map->file[i][j + 2] == '1')
			{
				map->map_start = i;
				break;
			}
		}
	}
	map->map = copy_2d_array(map->file, map->map_start, map->file_height);
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
	get_width(map);
	return (map);
}

/**
 * parse all the things in map into the struct
 */
int	parse_struct(t_map *map)
{
	map->map_height = map->file_height - 8;
	if (search(map->file, map->file_height, "NO") == -1
		|| search(map->file, map->file_height, "SO") == -1
		|| search(map->file, map->file_height, "WE") == -1
		|| search(map->file, map->file_height, "EA") == -1)
		ft_error("Invalid map");
	map = p_struct(map);
	error_handling(map);
	return (0);
}
