/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:24:56 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 14:05:23 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	initialize_map(t_map *map)
{
	if (!map)
		return ;
	map->map_height = 0;
	map->file_height = 0;
	map->map_width = 0;
	map->file = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->sprite = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->map = NULL;
}

/**
 * function to initialize the arg struct
 */
void	initialize_arg(t_arg *arg)
{
	if (!arg)
		return ;
	arg->map_add = NULL;
	initialize_map(&arg->map);
}
