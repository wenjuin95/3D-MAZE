/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 13:35:29 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->sout || !map->west || !map->east || !map->sprite
		|| !map->floor || !map->ceiling || !map->map_layout)
		ft_error("Fail to allocate memory");
}

int	parse_struct(t_map *map)
{
	map->mapl_len = map->map_height - 8;
	map->north = ft_substr(map->map[0], 3, ft_strlen(map->map[0]));
	map->sout = ft_substr(map->map[1], 3, ft_strlen(map->map[1]));
	map->west = ft_substr(map->map[2], 3, ft_strlen(map->map[2]));
	map->east = ft_substr(map->map[3], 3, ft_strlen(map->map[3]));
	map->sprite = ft_substr(map->map[4], 2, ft_strlen(map->map[4]));
	map->floor = set_rgb(ft_substr(map->map[5], 2, ft_strlen(map->map[5])));
	map->ceiling = set_rgb(ft_substr(map->map[6], 2, ft_strlen(map->map[6])));
	map->map_layout = copy_2d_array(map->map, 8, map->map_height);
	map->floor_hex = convert_rgb_to_hex(map->floor);
	map->ceiling_hex = convert_rgb_to_hex(map->ceiling);
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
	free_2d(src);
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
void	take_arg(int ac, char **av, t_arg *arg)
{
	if (ac != 2)
		ft_error("Wrong number of arguments");
	arg->map_add = ft_strdup(av[1]);
}
