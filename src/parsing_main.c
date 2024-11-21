/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/11/21 15:34:34 by chtan            ###   ########.fr       */
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

static void	error_handling(t_map *map)
{
	if (!map->north || !map->sout || !map->west || !map->east || !map->sprite
		|| !map->floor || !map->ceiling || !map->map_layout)
		ft_error("Fail to allocate memory");
}

char	*cut_first3(char *s, int len)
{
	int i;
	int j;
	char *str;
	
	i = 2;
	j = 0;
	str = malloc(sizeof(char) * len - 2);
	while (i < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	return (str);	
}

static int *tranfer(char *str)
{
	char **split;

	split = ft_split(str, ',');
	int *rgb = malloc(sizeof(int) * 3);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	if (!rgb)
		ft_error("Fail to allocate memory");
	return (rgb);
}

int	parse_struct(t_map *map)
{
	char *str;
	int i;

	i = 8;
	map->north = cut_first3(map->map[0], ft_strlen(map->map[0]));
	map->sout = cut_first3(map->map[1], ft_strlen(map->map[1]));
	map->west = cut_first3(map->map[2], ft_strlen(map->map[2]));
	map->east = cut_first3(map->map[3], ft_strlen(map->map[3]));
	map->sprite = cut_first(map->map[4], ft_strlen(map->map[4]));
	map->floor = tranfer(cut_first3(map->map[5], ft_strlen(map->map[5])));
	map->ceiling = tranfer(cut_first3(map->map[6], ft_strlen(map->map[6])));
	while (i < map->map_height)
	{
		ft_strlcpy(str, map->map[i], ft_strlen(map->map[i]) + 1);
		i++;
	}
	map->map_layout = ft_split(map->map[8], ' ');
	error_handling(map);
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
