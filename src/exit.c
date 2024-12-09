/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:31:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 00:16:18 by welow            ###   ########.fr       */
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

/**
 * @brief free the north, south, west, east, floor, and ceiling texture
 * @param texture the north, south, west, east, floor, and ceiling texture
*/
// void	free_texture(t_tex *texture)
// {
// 	if (texture->north != NULL)
// 		free(texture->north);
// 	if (texture->south != NULL)
// 		free(texture->south);
// 	if (texture->west != NULL)
// 		free(texture->west);
// 	if (texture->east != NULL)
// 		free(texture->east);
// 	if (texture->floor != NULL)
// 		free(texture->floor);
// 	if (texture->ceiling != NULL)
// 		free(texture->ceiling);
// }

/**
 * @brief free the mlx and win
 * @param data the data
 * @note 1. mlx_destroy_display : free the display
 * @note 2. mlx_destroy_window : free the window
*/
void	clean_mlx(t_data *data)
{
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

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

/**
 * @brief free the data struct
 * @param data the data to free
 * @note 1. free the map, tex_data, tex_pixel and texture
*/
void	clean_data(t_data *data)
{
	// if (data->tex_data)
	// 	free_array((void **)data->tex_data);
	// if (data->tex_pixel != NULL)
	// 	free_array((void **)data->tex_pixel);
	if (data->map_add != NULL)
		free(data->map_add);
	free_map(&data->map);
	// if (data->map != NULL)
	// 	free_array((void **)data->map);
	// free_texture(&data->texture);
}

/**
 * @brief clean the data that relate memory and exit
 * @param data the win, mlx, tex, tex_pixel, and map to free
 * @return void
*/
int	clean_and_exit(t_data *data)
{
	if (data == NULL)
		exit(EXIT_SUCCESS);
	// clean_mlx(data);
	clean_data(data);
	exit(EXIT_SUCCESS);
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
