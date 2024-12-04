/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/12/04 17:54:05 by chtan            ###   ########.fr       */
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
		perror("File is a directory ");
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
		ft_error("Fail to allocate memory");
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
	t_map *tmp;
	int i;

	i = 0;
	tmp = &arg->map;
	if (tmp->map_layout == NULL)
		ft_error("Fail to allocate memory");
	tmp->array_width = (int *)malloc(sizeof(int) * tmp->mapl_len);
	if (!tmp->array_width)
		ft_error("Fail to allocate memory for map_width");
	while(i < tmp->mapl_len)
	{
		tmp->array_width[i] = ft_strlen(arg->map.map_layout[i]);
		i++;
	}
	return (tmp);
}

int	get_width(t_map *map)
{
	int i;
	int	j;

	if (!map->map_layout || map->map_layout[0] == NULL) 
    	return (ft_error("Invalid ument structure"), 1);
	for(int i = 0; i < 	map->mapl_len; i++)
	{
		printf("%s\n", map->map_layout[i]);
	}
	i = ft_strlen(map->map_layout[0]);
	j = 1;
	while (j < map->mapl_len)
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
int	parse(int ac, char **av, t_arg *arg)
{
	take_arg(ac, av, arg);
	arg->map.map_height = get_line_nb(arg->map_add);
	if (arg->map.map_height == -1)
		return (1);
	arg->map.map = read_map_file(arg->map_add, arg->map.map_height);
	// check_map_wall(&arg->map);
	parse_struct(&arg->map);
	check_valid_element(arg);
	return (0);
}
