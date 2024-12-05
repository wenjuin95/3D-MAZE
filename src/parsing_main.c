/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/12/05 15:45:28 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

/**
 * get the number of lines in the file
 * for read the file
 */
static int	get_line_nb(char *file)
{
	int		fd;
	int		lines_num;
	char	*line;

	lines_num = 0;
	if (is_directory(file))
		return (perror("File is a directory "), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Fail to open file "), -1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines_num++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines_num == 0)
		return (perror("Map file is empty "), -1);
	close(fd);
	return (lines_num);
}

/**
 * read the file and store the map in a 2d array
 */
static char	**read_map_file(char *file, int lines_num)
{
	char	**map;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("Fail to open file");
	map = (char **)malloc(sizeof(char *) * (lines_num + 1));
	if (!map)
		perror("Fail to allocate memory");
	i = 0;
	while (i < lines_num)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}

t_map	*parse_width(t_arg *arg)
{
	t_map	*tmp;
	int		i;

	i = 0;
	tmp = &arg->map;
	if (tmp->map_layout == NULL)
		ft_error("Fail to allocate memory12");
	tmp->array_width = (int *)malloc(sizeof(int) * tmp->maply_height);
	if (!tmp->array_width)
		ft_error("Fail to allocate memory for map_width");
	while (i < tmp->maply_height)
	{
		tmp->array_width[i] = ft_strlen(arg->map.map_layout[i]);
		i++;
	}
	return (tmp);
}

int	get_width(t_map *map)
{
	int	i;
	int	j;

	if (!map->map_layout || map->map_layout[0] == NULL)
		return (ft_error("Invalid ument structure"), 1);
	i = ft_strlen(map->map_layout[0]);
	j = 1;
	while (j < map->maply_height)
	{
		if (i < ft_strlen(map->map_layout[j]))
			i = ft_strlen(map->map_layout[j]);
		j++;
	}
	return (i);
}

/**
 * this function is the main function of parsing
 * first parse the argument into struct (map address)
 * check the file name (need to end with .cub)
 * then read the file and store the map in a 2d array
 * lastly read the 2d array and parse each line into different variable
 * error handling
 */
int	parse(char **av, t_arg *arg)
{
	arg->map_add = ft_strdup(av[1]);
	check_valid_map_name(arg->map_add, ".cub");
	arg->map.map_height = get_line_nb(arg->map_add);
	if(arg->map.map_height == -1)
		return (ft_error("Fail to get line number"), 1);
	arg->map.map = read_map_file(arg->map_add, arg->map.map_height);
	parse_struct(&arg->map);
	check_valid_element(arg);
	if (check_map_sides(&arg->map, arg->map.map_layout) == 1)
		ft_error("Map not surrounded by wall");
	return (0);
}
