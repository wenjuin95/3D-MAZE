/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 10:52:44 by chtan            ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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

/***
 * @brief Check if the map is surrounded by wall
 * will need to use map height and array of width
 */
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
	while (++i < rows)
	{
		cur = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][cur - 1] != '1')
			return (1);
		if (cur >= prev
			&& ft_strspn(map[i] + prev - 1, "1") != cur - prev + 1)
			return (1);
		if (cur < prev
			&& ft_strspn(map[i - 1] + cur - 1, "1") != prev - cur + 1)
			return (1);
		prev = cur;
	}
	return (0);
}

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
				clean_and_exit(data);
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
