/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 00:07:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east
		|| !map->floor || !map->ceiling || !map->map_layout)
		ft_error("Fail to allocate memory56");
}

char	*cut_first3(char *s, int len, int start)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * (len - start + 1));
	while (i < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

// static int	check_true(t_map *map, int i)
// {
// 		bool res;

// 		res = false;
// }

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

/**
 * the variable i here is the index of the whole map
 * it's like a global variable for parsing
 */
int	parse_struct(t_map *map)
{
	map->maply_height = map->map_height - 8;
	if (search(map->map, map->map_height, "NO") == -1
		|| search(map->map, map->map_height, "SO") == -1
		|| search(map->map, map->map_height, "WE") == -1
		|| search(map->map, map->map_height, "EA") == -1)
		ft_error("Invalid map");
	map->north = remove_nl(ft_substr(map->map[search(map->map, map->map_height,
					"NO")], 3, ft_len(map->map[search2(map->map,
						map->map_height, "NO")])));
	map->south = remove_nl(ft_substr(map->map[search(map->map, map->map_height,
					"SO")], 3, ft_len(map->map[search2(map->map,
						map->map_height, "SO")])));
	map->west = remove_nl(ft_substr(map->map[search(map->map, map->map_height,
					"WE")], 3, ft_len(map->map[search2(map->map,
						map->map_height, "WE")])));
	map->east = remove_nl(ft_substr(map->map[search(map->map, map->map_height,
					"EA")], 3, ft_len(map->map[search2(map->map,
						map->map_height, "EA")])));
	// map->sprite = ft_substr(map->map[search(map->map, map->map_height, "S ")], 2, ft_strlen(map->map[4]));
	map->floor = set_rgb(remove_nl(ft_substr(map->map[5], 2,
					ft_strlen(map->map[5]))));
	map->ceiling = set_rgb(remove_nl(ft_substr(map->map[6], 2,
					ft_strlen(map->map[6]))));
	map->map_layout = copy_2d_array(map->map, 8, map->map_height);
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
	map->map_width = get_width(map);
	error_handling(map);
	return (0);
}
