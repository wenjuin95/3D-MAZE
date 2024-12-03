/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:40:48 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 23:41:28 by welow            ###   ########.fr       */
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

void	check_valid_element(t_data *data)
{
	t_map	*temp;
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	temp = &data->map;
	tmp = temp->map_layout;
	while (i < temp->mapl_len)
	{
		j = 0;
		while (tmp[i][j] != '\0')
		{
			if (tmp[i][j] != '1' && tmp[i][j] != '0' &&
			tmp[i][j] != 'N' && tmp[i][j] != 'S' && tmp[i][j] != 'E'
				&& tmp[i][j] != ' ' && tmp[i][j] != 'W'
				&& tmp[i][j] != '\n')
				ft_error("invalid char in map!");
			j++;
		}
		i++;
	}
	free_2d(tmp);
}
