/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:56:20 by chtan             #+#    #+#             */
/*   Updated: 2024/12/06 11:14:38 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include "cub3d.h"

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

typedef struct s_map
{
	int		maply_height;
	char	**map;
	int		map_height;
	int		*array_width;
	int		map_width;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		*floor;
	int		*ceiling;
	char	**map_layout;
	size_t	floor_hex;
	size_t	ceiling_hex;
}	t_map;

typedef struct s_arg
{
	char	*map_add;
	t_map	map;
}	t_arg;

// Free functions
void	free_arg(t_arg *arg);
void	free_2d(char **str);

//initialize
void	initialize_arg(t_arg *arg);

// parsing
int		parse(char **av, t_arg *arg);
int		parse_struct(t_map *map);
char	*cut_first3(char *s, int len, int start);
t_map	*parse_width(t_arg *arg);
int		get_width(t_map *map);
char	*remove_nl(char *src);

//check
void	check_valid_map_name(char *file, char *type);
bool	is_directory(char *file);
int		check_map_sides(t_map *map, char **map_tab);
void	check_valid_element(t_arg *arg);
int		check_valid_rgb(int *rgb);

//convert
int		*set_rgb(char *line);
size_t	convert_rgb_to_hex(int *rgb_tab);
char	**copy_2d_array(char **src, int start, int src_height);

//utils

#endif
