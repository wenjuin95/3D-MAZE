/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:31:44 by welow             #+#    #+#             */
/*   Updated: 2024/11/27 21:56:11 by welow            ###   ########.fr       */
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
 * @brief free the north, south, west, east texture
 * @param texture the north, south, west, east texture
*/
void	free_texture(t_tex *texture)
{
	if (texture->north != NULL)
		free(texture->north);
	if (texture->south != NULL)
		free(texture->south);
	if (texture->west != NULL)
		free(texture->west);
	if (texture->east != NULL)
		free(texture->east);
}

/**
 * @brief free the texture, tex, tex_pixel and map
 * @param data the texture, tex, tex_pixel and map
*/
void	free_texture_and_map(t_data *data)
{
	if (data->tex != NULL)
		free_array((void **)data->tex);
	if (data->tex_pixel != NULL)
		free_array((void **)data->tex_pixel);
	if (data->map != NULL)
		free_array((void **)data->map);
	free_texture(&data->texture);
}

/**
 * @brief clean the data that relate memory and exit
 * @param data the win, mlx, tex, tex_pixel, and map to free
 * @return void
*/
void	clean_and_exit(t_data *data)
{
	if (data == NULL)
		exit(EXIT_SUCCESS);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
		free(data->mlx);
	free_texture_and_map(data);
	exit(EXIT_SUCCESS);
}

/**
 * @brief button to execute close window
 * @param parse the mlx and win to close and free
 * @return 0 mean success
*/
int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}
