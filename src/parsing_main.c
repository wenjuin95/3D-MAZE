/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/12/02 16:38:48 by chtan            ###   ########.fr       */
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
	tmp->map_width = (int *)malloc(sizeof(int) * tmp->mapl_len);
	if (!tmp->map_width)
		ft_error("Fail to allocate memory for map_width");
	while(i < tmp->mapl_len)
	{
		tmp->map_width[i] = ft_strlen(arg->map.map_layout[i]);
		i++;
	}
	return (tmp);
}

int	parse(int ac, char **av, t_arg *arg)
{
	take_arg(ac, av, arg);
	check_valid_map_name(arg->map_add, ".cub");
	arg->map.map_height = get_line_nb(arg->map_add);
	if (arg->map.map_height == -1)
		return (1);
	arg->map.map = read_map_file(arg->map_add, arg->map.map_height);
	check_valid_element(arg);
	// check_map_wall(&arg->map);
	parse_struct(&arg->map);
	arg->map = *parse_width(arg);
	return (0);
}
