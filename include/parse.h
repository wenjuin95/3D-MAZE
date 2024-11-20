/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:56:20 by chtan             #+#    #+#             */
/*   Updated: 2024/11/20 17:05:56 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "cub3d.h"

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
    char    *map_add;//map address

    char    *north;
    char    *sout;
    char    *west;
    char    *east;
    char    *sprite;
    char    *floor;
    char    *ceiling;
    char    **map_layout;
}               t_map;

typedef struct s_arg
{
    char    *map_add;//map address
    t_map   map;
}               t_arg;

// parsing
void    take_arg(int argc, char **argv, t_arg *arg);
int     parse(int ac, char **av, t_arg *arg);

//check
void	check_valid_map_name(char *file, char *type);

#endif