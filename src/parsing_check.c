/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 00:07:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Check map to make sure it is a .cub file
 */
void	check_valid_map_name(char *file, char *type)
{
	int		i;
	char	*extension;

	i = ft_strlen(file) - 4;
	extension = ft_substr(file, i, 4);
	if (ft_strncmp(type, extension, 4) != 0)
	{
		free(extension);
		ft_error("wrong file type");
	}
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

void	check_valid_element(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->map.maply_height)
	{
		j = 0;
		while (data->map.map_layout[i][j] != '\0')
		{
			if (data->map.map_layout[i][j] != '1'
			&& data->map.map_layout[i][j] != '0'
			&& data->map.map_layout[i][j] != 'N' && data->map.map_layout[i][j] != 'S'
				&& data->map.map_layout[i][j] != 'E'
				&& data->map.map_layout[i][j] != ' '
				&& data->map.map_layout[i][j] != 'W'
				&& data->map.map_layout[i][j] != '\n')
			{
				ft_error("invalid char in map!");
				return ;
			}
			j++;
		}
		i++;
	}
}
