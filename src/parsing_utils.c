/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 23:50:48 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east || !map->sprite
		|| !map->floor || !map->ceiling || !map->map_layout)
		ft_error("Fail to allocate memory");
}

int	parse_struct(t_map *map)
{
	map->mapl_len = map->map_height - 8;
	map->north = ft_substr(map->map[0], 3, ft_strlen(map->map[0]));
	map->south = ft_substr(map->map[1], 3, ft_strlen(map->map[1]));
	map->west = ft_substr(map->map[2], 3, ft_strlen(map->map[2]));
	map->east = ft_substr(map->map[3], 3, ft_strlen(map->map[3]));
	map->sprite = ft_substr(map->map[4], 2, ft_strlen(map->map[4]));
	map->floor = set_rgb(ft_substr(map->map[5], 2, ft_strlen(map->map[5])));
	map->ceiling = set_rgb(ft_substr(map->map[6], 2, ft_strlen(map->map[6])));
	map->map_layout = copy_2d_array(map->map, 8, map->map_height);
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
	//note: need player position
	error_handling(map);
	return (0);
}

char	**copy_2d_array(char **src, int start, int src_height)
{
	int		j;
	char	**dest;

	j = 0;
	dest = malloc(sizeof(char *) * (src_height - start + 1));
	while (start < src_height)
	{
		dest[j] = ft_strdup(src[start]);
		start++;
		j++;
	}
	dest[j] = NULL;
	free_array((void **)src);
	return (dest);
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

/**
 * the function is parse the arg to the struct
 */
void	take_arg(int ac, char **av, t_data *data)
{
	if (ac != 2)
		ft_error("Wrong number of arguments");
	data->map_add = ft_strdup(av[1]);
}
