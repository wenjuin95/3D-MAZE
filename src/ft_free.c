/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:41:39 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 13:51:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_map(t_map *map)
{
	int	i;

	free(map->north);
	free(map->sout);
	free(map->west);
	free(map->east);
	free(map->sprite);
	free(map->floor);
	free(map->ceiling);
	i = -1;
	while (++i < map->map_height - 8)
		free(map->map_layout[i]);
	free(map->map_layout);
	free(map->map_width);
}

void	free_arg(t_data *data)
{
	if (data->map_add != NULL)
		free(data->map_add);
	free_map(&data->map);
}
