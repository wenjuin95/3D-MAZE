/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:41:39 by chtan             #+#    #+#             */
/*   Updated: 2024/11/24 11:33:07 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void free_map(t_map *map)
{
    int i;

    i = 0;
    if (map->map && map->map[i])
    {
        while (i < map->map_height)
            free(map->map[i++]);
        free(map->map);
    }
    free(map->north);
    free(map->sout);
    free(map->west);
    free(map->east);
    free(map->sprite);
    free(map->floor);
    free(map->ceiling);
    i = -1;
    if (map->map_layout)
    {
        while(++i < map->map_height - 8)
            free(map->map_layout[i]);
        free(map->map_layout);
    }
}

void free_arg(t_arg *arg)
{
    // if (arg->map_add != NULL)
    //     free(arg->map_add);
    free_map(&arg->map);
}