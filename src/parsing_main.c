/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/11/24 11:13:50 by chtan            ###   ########.fr       */
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
	char	*str;

	lines_num = 0;
	if (is_directory(file))
		ft_error("File is a directory");
	fd = open(file, O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		lines_num++;
		free(str);
	}
	if (lines_num == 0)
		return (ft_error("Map file is empty"), -1);
	close(fd);
	return (lines_num);
}

/**
 * the function is parse the arg to the struct
 */
void    take_arg(int argc, char **argv, t_arg *arg)
{
    if (argc != 2)
        ft_error("Wrong number of arguments");
    arg->map_add = argv[1];
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

// static int *tranfer(char *str)
// {
// 	char **split;

// 	split = ft_split(str, ',');
// 	if (!split)
// 		ft_error("Fail to allocate memory");
// 	int *rgb = malloc(sizeof(int) * 3);
// 	rgb[0] = ft_atoi(split[0]);
// 	rgb[1] = ft_atoi(split[1]);
// 	rgb[2] = ft_atoi(split[2]);
// 	if (!rgb)
// 		ft_error("Fail to allocate memory");
// 	return (rgb);
char	**copy_2d_array(char **src, int start, int src_height)
{
    int j;
	int i;
	char **dest;

	i = start;
	j = 0;
	dest = malloc(sizeof(char *) * src_height);
    while(i < src_height)
    {
        ft_strlcpy(dest[j], src[i], ft_strlen(src[i]) - 1);
		j++;
		i++;
    }
	free_2d(src);
	j = -1;
	while (++j)
		printf("map = %s\n", dest[j]);
	return (dest);
}

int	parse_struct(t_map *map)
{
	map->north = cut_first3(map->map[0], ft_strlen(map->map[0]));
	map->sout = cut_first3(map->map[1], ft_strlen(map->map[1]));
	map->west = cut_first3(map->map[2], ft_strlen(map->map[2]));
	map->east = cut_first3(map->map[3], ft_strlen(map->map[3]));
	map->sprite = cut_first3(map->map[4], ft_strlen(map->map[4]));
	map->floor = set_rgb(cut_first3(map->map[5], ft_strlen(map->map[5])));
	map->ceiling = set_rgb(cut_first3(map->map[6], ft_strlen(map->map[6])));
	map->map_layout = copy_2d_array(map->map, 8, map->map_height);
	printf("ok\n\n\n");
	error_handling(map);
	return (0);
}

int	parse(int ac, char **av, t_arg *arg)
{
    take_arg(ac, av, arg);
	check_valid_map_name(arg->map_add, ".cub");
    arg->map.map_height = get_line_nb(av[1]);
	if (arg->map.map_height == -1)
		return (1);
    arg->map.map = read_map_file(av[1], arg->map.map_height);
	parse_struct(&arg->map);
    return (0); 
}
