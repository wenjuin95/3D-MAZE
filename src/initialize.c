/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:47:53 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 00:20:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief initialize data
 * @param data data to initialize
 * @note 1. initialize the data to all null and zero
 * @note 2. initialize the window height and width
 * @note 3. initialize the texture size
*/
void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	data->texture.texture_size = TEXTURE_SIZE;
}

/**
 * @brief initialize mlx
 * @param data data to initialize
 * @return 0 if success, 1 if failed
*/
int	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		clean_and_exit(data);
		return (1);
	}
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"cub3D");
	if (data->win == NULL)
	{
		clean_and_exit(data);
		return (1);
	}
	return (0);
}

/**
 * @brief initialize key and image rendering
 * @param data data to initialize
 * @note 1. mlx_hook is a function to handle the event
 * @note 2. mlx_mouse_hide is a function to hide the mouse cursor
 * @note 3. mlx_loop_hook is a function to keep load the function
*/
void	initialize_mlx_hook(t_data *data)
{
	mlx_hook(data->win, DestroyNotify, NoEventMask, close_win, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, handle_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, handle_key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, handle_mouse, data);
	// mlx_mouse_hide(data->mlx, data->win);
	mlx_loop_hook(data->mlx, update_image, data);
}

/**
 * @brief create a image memory
 * @param data get mlx pointer
 * @param img get img pointer
 * @param width get the window width
 * @param height get the window height
 * @note 1. initialize all the img struct to 0 to prevent garbage value
 * @note 4. mlx_new_image is a function to allocate memory for a image
 * @note 5. mlx_get_data_addr is a function to get the address of the image
*/
void	initialize_image(t_data *data, t_img *img, int w_width, int w_height)
{
	img->img = mlx_new_image(data->mlx, w_width, w_height);
	if (img->img == NULL)
		clean_and_exit(data);
	img->img_addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->size_line, &img->endian);
}

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
