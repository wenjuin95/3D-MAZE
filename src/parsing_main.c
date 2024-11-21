/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/11/20 20:05:55 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int	get_line_nb(char *file)
{
	int		fd;
	int		lines_num;
	char	*str;

	lines_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Fail to open file");
	str = get_next_line(fd);
	while (str)
	{
		lines_num++;
		free(str);
		str = get_next_line(fd);
	}
	if (lines_num == 0)
		ft_error("Map file is empty");
	close(fd);
	return (lines_num);
}

void    take_arg(int argc, char **argv, t_arg *arg)
{
    if (argc != 2)
        ft_error("Wrong number of arguments");
    arg->map_add = argv[1];
    printf("Map address : %s\n", arg->map_add);
}

static char	**read_map_file(char *file, int lines_num)
{
	char	**map;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Fail to open file");
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

int	parse_struct(t_map *map)
{
	map->north = map->map[0];
	map->sout = map->map[1];
	map->west = map->map[2];
	map->east = map->map[3];
	map->sprite = map->map[4];
	map->floor = map->map[5];
	map->ceiling = map->map[6];
	map->map_layout = map->map + 8;
	return (0);
}

int parse(int ac, char **av, t_arg *arg)
{
    take_arg(ac, av, arg);
	check_valid_map_name(arg->map_add, ".cub");
    arg->map.map_height = get_line_nb(arg->map.map_add);
    arg->map.map = read_map_file(arg->map.map_add, arg->map.map_height);
	parse_struct(&arg->map);
    return (0); 
}
