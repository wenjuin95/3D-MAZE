/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:41:39 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 14:21:06 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	free_map(t_map *map)
{
	int	i;

	free(map->north);
	free(map->south);
	free(map->west);
	free(map->east);
	free(map->sprite);
	free(map->floor);
	free(map->ceiling);
	i = -1;
	while (++i < map->file_height - 8)
		free(map->map[i]);
	free(map->map);
	// free(map->map_width);
}

void	free_arg(t_arg *arg)
{
	if (arg->map_add != NULL)
		free(arg->map_add);
	free_map(&arg->map);
}
