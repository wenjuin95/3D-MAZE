/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:41:39 by chtan             #+#    #+#             */
/*   Updated: 2024/12/05 18:00:22 by welow            ###   ########.fr       */
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
	while (++i < map->map_height - 8)
		free(map->map_layout[i]);
	free(map->map_layout);
	// free(map->array_width);
}

void	free_arg(t_arg *arg)
{
	if (arg->map_add != NULL)
		free(arg->map_add);
	free_map(&arg->map);
}
