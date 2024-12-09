/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:24:56 by chtan             #+#    #+#             */
/*   Updated: 2024/12/09 23:03:46 by welow            ###   ########.fr       */
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
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->sprite = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->map_layout = NULL;
}

void	initialize_arg(t_data *data)
{
	if (!data)
		return ;
	data->map_add = NULL;
	initialize_map(&data->map);
}
