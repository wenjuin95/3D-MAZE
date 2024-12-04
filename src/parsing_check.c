/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/04 18:06:18 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

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

static int skip_space(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

/***
 * @brief Check if the map is surrounded by wall
 * will need to use map_layout height and array of width
 */
void	check_map_wall(t_map *map)
{
	int	i;
	int	j;
	int	width;
	
	i = 0;
	while (i < map->mapl_len)
	{
		j = skip_space(map->map_layout[i], 0);
		width = ft_strlen(map->map_layout[i]);
		while (j < width)
		{
			if (i == 0 || i == map->map_height - 1 || j == 0 || j == width - 1)
			{
				if (map->map_layout[i][j] != '1')
					ft_error("map not surrounded by wall!");
			}
			j++;
		}
		i++;
	}
}

void	check_valid_element(t_arg *arg)
{
	t_map	*temp;
	int	i;
	int	j;

	i = 0;
	temp = &arg->map;
	while (i < temp->mapl_len)
	{
		j = 0;
		while (temp->map_layout[i][j] != '\0')
		{
			if (temp->map_layout[i][j] != '1' && temp->map_layout[i][j] != '0' &&
			temp->map_layout[i][j] != 'N' && temp->map_layout[i][j] != 'S' && temp->map_layout[i][j] != 'E'
				&& temp->map_layout[i][j] != ' ' && temp->map_layout[i][j] != 'W'
				&& temp->map_layout[i][j] != '\n')
				ft_error("invalid char in map!");
			j++;
		}
		i++;
	}
}
