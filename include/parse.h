/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/31 12:41:08 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_H
# define PARSE_H

// # include <stdlib.h>
// # include <stdio.h>
// # include <unistd.h>
// # include <errno.h>
// # include <stdbool.h>
// # include "cub3d.h"

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

typedef struct s_data	t_data;
// typedef struct s_map
// {
// 	int		maply_height;
// 	char	**map;
// 	int		map_height;
// 	int		*array_width;
// 	int		map_width;
// 	char	*north;
// 	char	*south;
// 	char	*west;
// 	char	*east;
// 	char	*sprite;
// 	int		*floor;
// 	int		*ceiling;
// 	char	**map_layout;
// 	size_t	floor_hex;
// 	size_t	ceiling_hex;
// }	t_map;

// typedef struct s_player
// {
// 	char	dir;
// 	double	pos_x;
// 	double	pos_y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// }	t_player;

// typedef struct s_data
// {
// 	char	*map_add;
// 	t_map	map;
// 	t_player	player;
// }	t_data;

//initialize
void	initialize_arg(t_data *data);

// parsing
int		parse(char **av, t_data *data);
int		parse_struct(t_map *map);
t_map	*parse_width(t_data *data);
int		get_width(t_map *map);
char	*remove_nl(char *src);
int     ft_strspn(const char *s, const char *accept);
int     search(char **array, int rows, char *target);

//check
void	check_valid_map_name(char *file, char *type);
bool	is_directory(char *file);
int		check_map_sides(t_map *map, char **map_tab);
void	check_valid_element(t_data *data);
int		check_valid_rgb(int *rgb);
int		check_num_players(char **map);
int		parse_check(t_data *data);
int		check_map_closed(char **map, int rows);
void	check_map(t_data *data);
int		check_map_details(t_data *data);
void	flood_fill_recursive(char **map, int i, int j, int height);
int     flood_fill(char **map, int height);
int	    check_enclosed_space(char **map, int rows);
int     check_file(char *file);
void	error_handling(t_map *map);
void	error_handling2(t_map *map);

//convert
int		*set_rgb(char *line);
size_t	convert_rgb_to_hex(int *rgb_tab);
char	**copy_2d_array(char **src, int start, int src_height);

//utils
char	**duplicate_map(char **map, int rows);

#endif
