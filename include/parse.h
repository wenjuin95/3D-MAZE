/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:56:20 by chtan             #+#    #+#             */
/*   Updated: 2024/12/02 10:52:37 by chtan            ###   ########.fr       */
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
	int		mapl_len;
	char	**map;
	int		map_height;
	int		map_width;
	char	*north;
	char	*sout;
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
void	take_arg(int argc, char **argv, t_arg *arg);
int		parse(int ac, char **av, t_arg *arg);
int		parse_struct(t_map *map);
char	*cut_first3(char *s, int len, int start);

//check
void	check_valid_map_name(char *file, char *type);
bool	is_directory(char *file);
void	check_map_wall(t_map *map);
void	check_valid_element(char **buffer);
void	check_valid_element(char **buffer);

//convert
int		*set_rgb(char *line);
size_t	convert_rgb_to_hex(int *rgb_tab);
char	**copy_2d_array(char **src, int start, int src_height);

//tmp

#endif
