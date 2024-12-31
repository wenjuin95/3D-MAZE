/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 12:52:16 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * the function will serch the target(keyword) in the 2d array
 * and return the index of the row
 * else return -1 means error / not found
 */
int	search(char **array, int rows, char *target)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(target);
	while (i < rows)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == tmp[0] && array[i][j + 1] == tmp[1])
				return (free(tmp), i);
			j++;
		}
		i++;
	}
	free(tmp);
	return (-1);
}

/**
 * the function is to find where is the map start
 * the map start is the first row of the map
 */
static void	find(t_map *map, int file_height, char **file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!file)
		(ft_error("Fail to allocate memory"), exit(1));
	while (i < file_height)
	{
		j = 0;
		while (j < ft_strlen(file[i]))
		{
			if (file[i][j] == '1' && file[i][j + 1] == '1'
				&& file[i][j + 2] == '1')
			{
				map->map_start = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * this function is to skip keywords && spaces && tabs
 * and return the index of the first character of address
 */
static int	find_index(char *s, char *type)
{
	int	i;

	i = 0;
	while (s[i] == 32 || s[i] == '\t')
		i++;
	if (s[i] == type[0] && s[i + 1] == type[1])
		i += 2;
	while (s[i] == 32 || s[i] == '\t')
		i++;
	return (i);
}

/**
 * the len is not constant, need to change
 * create a function to skip is_space
 */
static char	*combine(t_map *map, char *type)
{
	int		i;
	char	*str;
	int		len;

	i = search(map->file, map->file_height, type);
	len = find_index(map->file[i], type);
	str = remove_nl(ft_substr(map->file[i], len, ft_len(map->file[i])));
	if (!str)
		(ft_error("Fail to allocate memory"), exit(1));
	return (str);
}

/**
 * the variable i here is the index of the whole map
 * it's like a global variable for parsing
 */
int	parse_struct(t_map *map)
{
	error_handling(map);
	find(map, map->file_height, map->file);
	map->map = copy_2d_array(map->file, map->map_start, map->file_height);
	map->north = combine(map, "NO");
	map->south = combine(map, "SO");
	map->west = combine(map, "WE");
	map->east = combine(map, "EA");
	map->floor = set_rgb(combine(map, "F "));
	map->ceiling = set_rgb(combine(map, "C "));
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
	map->map_width = get_width(map);
	map->map_height = map->file_height - map->map_start;
	error_handling2(map);
	return (0);
}
