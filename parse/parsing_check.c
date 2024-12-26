/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/27 00:23:04 by welow            ###   ########.fr       */
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
 * will need to use map height and array of width
 */
// static int	check_top_or_bottom(char **map_tab, int i, int j)
// {
// 	if (!map_tab || !map_tab[i] || !map_tab[i][j])
// 		return (1);
// 	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
// 	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
// 	|| map_tab[i][j] == '\f')
// 		j++;
// 	while (map_tab[i][j])
// 	{
// 		if (map_tab[i][j] != '1' && map_tab[i][j] != ' ')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

int	check_map_closed(char **map, int rows)
{
	int	i;
	int	prev;
	int	cur;

	i = 0;
	prev = ft_strlen(map[0]);
	if (ft_strspn(map[0], "1") != prev
		|| ft_strspn(map[rows - 1], "1") != (int)ft_strlen(map[rows - 1]))
		return (1);
	while (++i < rows - 1)
	{
		cur = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][cur - 1] != '1')
			return (1);
		if (cur > prev
			&& ft_strspn(map[i] + prev - 1, "1") != cur - prev + 1)
			return (1);
		if (cur < prev
			&& ft_strspn(map[i - 1] + cur - 1, "1") != prev - cur + 1)
			return (1);
		prev = cur;
	}
	return (0);
}

// void	check_map_wall(t_map *map)
// {
// 	int	i;
// 	int	j;
// 	int	width;

// 	i = 0;
// 	while (i < map->map_height)
// 	{
// 		j = skip_space(map->map[i], 0);
// 		width = ft_strlen(map->map[i]);
// 		while (j < width)
// 		{
// 			if (i == 0 || i == map->file_height - 1 || j == 0 || j == width - 1)
// 			{
// 				if (map->map[i][j] != '1')
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
	while (i < data->map.map_height)
	{
		j = 0;
		while (data->map.map[i][j] != '\0')
		{
			if (data->map.map[i][j] != '1'
			&& data->map.map[i][j] != '0'
			&& data->map.map[i][j] != 'N' && data->map.map[i][j] != 'S'
				&& data->map.map[i][j] != 'E'
				&& data->map.map[i][j] != ' '
				&& data->map.map[i][j] != 'W'
				&& data->map.map[i][j] != '\n')
			{
				ft_error("invalid char in map!");
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_num_players(char **map)
{
	int	i;
	int	j;
	int	num_players;

	i = -1;
	num_players = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				num_players++;
			j++;
		}
	}
	if (num_players != 1)
		return (1);
	return (0);
}
