/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/12 13:57:56 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east
		|| !map->floor || !map->ceiling || !map->map)
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

static void find(t_map *map, int file_height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < file_height)
	{
		j = 0;
		while (j < ft_strlen(map->file[i + 1]))
		{
			if (map->file[i][j] == '1' && map->file[i][j + 1] == '1' && map->file[i][j + 2] == '1')
			{
				map->map_start = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	error_handling2(t_map *map)
{
		if (search(map->file, map->file_height, "NO") == -1
		|| search(map->file, map->file_height, "SO") == -1
		|| search(map->file, map->file_height, "WE") == -1
		|| search(map->file, map->file_height, "EA") == -1)
		ft_error("Invalid map"), exit(1);
}
/**
 * the variable i here is the index of the whole map
 * it's like a global variable for parsing
 */
int	parse_struct(t_map *map)
{
	error_handling2(map);
	find(map, map->file_height);
	map->map = copy_2d_array(map->file, map->map_start, map->file_height);
	// for(int l = 0; map->map[l]; l++)
	// {
	// 	printf("(%s)\n", map->map[l]);
	// }
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
	map->floor = set_rgb(remove_nl(ft_substr(map->file[5], 2,
					ft_strlen(map->file[5]))));
	map->ceiling = set_rgb(remove_nl(ft_substr(map->file[6], 2,
					ft_strlen(map->file[6]))));
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
	map->map_width = get_width(map);
	error_handling(map);
	return (0);
}
