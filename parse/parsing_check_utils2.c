/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:21:56 by chtan             #+#    #+#             */
/*   Updated: 2024/12/31 11:38:54 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 *  all the elements here is neccessary so if any of them is missing
 *    it will return an error and exit
 */
void    error_handling(t_map *map)
{
    if (search(map->file, map->file_height, "NO") == -1
        || search(map->file, map->file_height, "SO") == -1
        || search(map->file, map->file_height, "WE") == -1
        || search(map->file, map->file_height, "EA") == -1
        || search(map->file, map->file_height, "F ") == -1
        || search(map->file, map->file_height, "C ") == -1)
        (ft_error("Invalid map"), exit(1));
}

char    **duplicate_map(char **map, int rows)
{
    char    **temp_map;
    int        i;

    i = 0;
    temp_map = ft_calloc(rows + 1, sizeof(char *));
    if (temp_map == NULL)
        return (NULL);
    while (map[i])
    {
        temp_map[i] = ft_strdup(map[i]);
        if (temp_map[i] == NULL)
        {
            free_array((void **)temp_map);
            return (NULL);
        }
        i++;
    }
    return (temp_map);
}
