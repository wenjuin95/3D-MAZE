/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/09 10:51:17 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

/**
 * @brief Check map to make sure it is a .cub file or tetxure file
 */
void	check_valid_map_name(char *file, char *type)
{
	int		i;
	char	*extension;

	i = ft_strlen(file) - 4;
	extension = ft_substr(file, i, 4);
	if (ft_strncmp(type, extension, 4) != 0)
		ft_error("wrong file type");
	free(extension);
}

bool	is_directory(char *file)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

// static int	skip_space(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	return (i);
// }

/***
 * @brief Check if the map is surrounded by wall
 * will need to use map_layout height and array of width
 */
static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (1);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1' && map_tab[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_sides(t_map *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == 1)
		return (1);
	i = 1;
	while (i < (map->maply_height - 1))
	{
		j = 0;
		while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
		|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
		|| map_tab[i][j] == '\f')
			j++;
		if (map_tab[i][j] != '1')
			return (1);
		j = ft_strlen(map_tab[i]) - 1;
		while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
		|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
		|| map_tab[i][j] == '\f')
			j--;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == 1)
		return (1);
	return (0);
}

// void	check_map_wall(t_map *map)
// {
// 	int	i;
// 	int	j;
// 	int	width;

// 	i = 0;
// 	while (i < map->maply_height)
// 	{
// 		j = skip_space(map->map_layout[i], 0);
// 		width = ft_strlen(map->map_layout[i]);
// 		while (j < width)
// 		{
// 			if (i == 0 || i == map->map_height - 1 || j == 0 || j == width - 1)
// 			{
// 				if (map->map_layout[i][j] != '1')
// 					ft_error("map not surrounded by wall!");
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	check_valid_element(t_arg *arg)
{
	int		i;
	int		j;

	i = 0;
	while (i < arg->map.maply_height)
	{
		j = 0;
		while (arg->map.map_layout[i][j] != '\0')
		{
			if (arg->map.map_layout[i][j] != '1'
			&& arg->map.map_layout[i][j] != '0'
			&& arg->map.map_layout[i][j] != 'N' && arg->map.map_layout[i][j] != 'S'
				&& arg->map.map_layout[i][j] != 'E'
				&& arg->map.map_layout[i][j] != ' '
				&& arg->map.map_layout[i][j] != 'W'
				&& arg->map.map_layout[i][j] != '\n')
			{
				ft_error("invalid char in map!");
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_map_closed(char **map, int rows)
{
	int	i;
	int	j;

	// Check top and bottom rows
	if (check_top_or_bottom(map, 0, 0) == 1 || check_top_or_bottom(map, rows - 1, 0) == 1)
		return (1);

	// Check left and right sides of each row
	for (i = 1; i < rows - 1; i++)
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if (map[i][j] != '1')
			return (1);
		j = ft_strlen(map[i]) - 1;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j--;
		if (map[i][j] != '1')
			return (1);
	}
	return (0);
}
