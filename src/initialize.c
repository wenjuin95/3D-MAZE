/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:24:56 by chtan             #+#    #+#             */
/*   Updated: 2024/12/04 18:11:33 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	initialize_map(t_map *map)
{
	if (!map)
		return ;
	map->maply_height = 0;
	map->map_height = 0;
	map->map_width = 0;
	map->map = NULL;
	map->north = NULL;
	map->sout = NULL;
	map->west = NULL;
	map->east = NULL;
	map->sprite = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->map_layout = NULL;
}

void	initialize_arg(t_arg *arg)
{
	if (!arg)
		return ;
	arg->map_add = NULL;
	initialize_map(&arg->map);
}
