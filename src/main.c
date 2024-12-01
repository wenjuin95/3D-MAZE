/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/01 00:40:01 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_width = SCREEN_W;
	data->win_height = SCREEN_H;
	data->texture.texture_size = TEXTURE_SIZE;
}
//////////////////////////////////////////////////////////////////////////////////

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		clean_and_exit(data);
	if (keycode == W)
		data->player.moved_y = 1;
	if (keycode == S)
		data->player.moved_y = -1;
	if (keycode == A)
		data->player.moved_x = -1;
	if (keycode == D)
		data->player.moved_x = 1;
	if (keycode == LEFT)
		data->player.rotated -= 1;
	if (keycode == RIGHT)
		data->player.rotated += 1;
	return (0);
}

//////////////////////////////////////////////////////////////////////////////////

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
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (data.win == NULL)
		return (1);
	initialize_img(&data);
	render_image(&data);
	debuger(&data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_key_press, &data);
	// mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_key_release, &data); //not yet
	// mlx_loop_hook(data.mlx, rendering, &data); //not yet
	mlx_loop(data.mlx);
}
