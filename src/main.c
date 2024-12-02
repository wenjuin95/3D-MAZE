/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/02 14:41:15 by welow            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parsing(&data, av) == 1)
		return (1);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (data.win == NULL)
		return (1);
	initialize_texture(&data);
	render_the_image(&data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_key_release, &data);
	mlx_loop_hook(data.mlx, update_image, &data);
	debuger(&data);
	mlx_loop(data.mlx);
}
