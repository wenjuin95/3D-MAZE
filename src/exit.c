/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:31:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/13 11:24:27 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief free 2d array
 * @param array the 2d array to free
*/
void	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	if (array != NULL)
		free(array);
}

static void	free_map(t_map *map)
{
	free(map->north);
	free(map->south);
	free(map->west);
	free(map->east);
	free(map->sprite);
	free(map->floor);
	free(map->ceiling);
	free_array((void **)map->map_layout);
}

/**
 * @brief free the data struct
 * @param data the data to free
 * @note 1. free the map, tex_data, tex_pixel and texture
*/
void	clean_data(t_data *data)
{
	if (data->tex_data)
		free_array((void **)data->tex_data);
	if (data->tex_pixel != NULL)
		free_array((void **)data->tex_pixel);
	if (data->map_add != NULL)
		free(data->map_add);
	free_map(&data->map);
}

/**
 * @brief clean the data that relate memory and exit
 * @param data the win, mlx, tex, tex_pixel, and map to free
 * @return void
*/
int	clean_and_exit(t_data *data)
{
	if (data == NULL)
		exit(1);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_data(data);
	exit(1);
}

/**
 * @brief button to execute close window
 * @param parse the mlx and win to close and free
 * @return 0 mean success
*/
int	close_win(t_data *data)
{
	clean_and_exit(data);
	return (0);
}
