/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 14:23:31 by chtan            ###   ########.fr       */
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
	char	**file_map;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || lines_num <= 0)
		return (perror("Fail to open file"), (NULL));
	file_map = (char **)malloc(sizeof(char *) * (lines_num + 1));
	if (!file_map)
		return (perror("Fail to allocate memory"), (NULL));
	i = 0;
	while (i < lines_num)
	{
		file_map[i] = get_next_line(fd);
		if (!file_map[i])
		{
			perror("Fail to read file");
			break ;
		}
		i++;
	}
	file_map[i] = NULL;
	close(fd);
	return (file_map);
}

t_map	*parse_width(t_arg *arg)
{
	t_map	*tmp;
	int		i;

	i = 0;
	tmp = &arg->map;
	if (tmp->map == NULL)
		ft_error("Fail to allocate memory12");
	tmp->map_width = (int *)malloc(sizeof(int) * tmp->map_height);
	if (!tmp->map_width)
		ft_error("Fail to allocate memory for map_width");
	while (i < tmp->map_height)
	{
		tmp->map_width[i] = ft_strlen(arg->map.map[i]);
		i++;
	}
	return (tmp);
}

void	get_width(t_map *map)
{
	int len;
	int	i;

	for(i = 0; i < map->map_height; i++)
	{
		printf("width[%d] = %d\n", i, map->map_width[i]);
	}
	len = map->map_width[0];
	i = 1;
	while (i < map->map_height)
	{
		if (map->map_width[i] > len)
			len = map->map_width[i];
		i++;
	}
	map->width = len;
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
	check_valid_file_name(arg->map_add, ".cub");
	arg->map.file_height = get_line_nb(arg->map_add);
	if(arg->map.file_height == -1)
		return (ft_error("Fail to get line number"), 1);
	arg->map.file = read_map_file(arg->map_add, arg->map.file_height);
	if (!arg->map.file)
		return (ft_error("Fail to read map file"), 1);
	parse_struct(&arg->map);
	check_valid_element(arg);
	if (check_map_closed(arg->map.map, arg->map.map_height))
	{
		ft_error("Map not surrounded by wall");
		exit(1);
	}
	return (0);
}
