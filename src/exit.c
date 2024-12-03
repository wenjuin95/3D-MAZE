/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:31:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 23:52:35 by welow            ###   ########.fr       */
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

	if (array == NULL)
		return ;
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
void	free_texture(t_map *texture)
{
	if (texture->north != NULL)
		free(texture->north);
	if (texture->south != NULL)
		free(texture->south);
	if (texture->west != NULL)
		free(texture->west);
	if (texture->east != NULL)
		free(texture->east);
	if (texture->floor != NULL)
		free(texture->floor);
	if (texture->ceiling != NULL)
		free(texture->ceiling);
}

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

/**
 * @brief free the data struct
 * @param data the data to free
 * @note 1. free the map, tex_data, tex_pixel and texture
*/
void	clean_data(t_data *data)
{
	if (data->map.map_layout != NULL)
		free_array((void **)data->map.map_layout);
	if (data->tex_data)
		free_array((void **)data->tex_data);
	if (data->tex_pixel != NULL)
		free_array((void **)data->tex_pixel);
	free_texture(&data->map);
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
	clean_mlx(data);
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
