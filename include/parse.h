/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:56:20 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 23:13:42 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

typedef struct s_data	t_data;

// Free functions
void	free_arg(t_data *data);
void	free_2d(char **str);

//initialize
void	initialize_arg(t_data *data);

// parsing
void	take_arg(int argc, char **argv, t_data *data);
int		parse(int ac, char **av, t_data *data);
int		parse_struct(t_map *map);
char	*cut_first3(char *s, int len, int start);
t_map	*parse_width(t_data *data);

//check
void	check_valid_map_name(char *file, char *type);
bool	is_directory(char *file);
void	check_map_wall(t_map *map);
void	check_valid_element(t_data *data);
void	ft_error(char *str);

//convert
int		*set_rgb(char *line);
size_t	convert_rgb_to_hex(int *rgb_tab);
char	**copy_2d_array(char **src, int start, int src_height);


#endif
