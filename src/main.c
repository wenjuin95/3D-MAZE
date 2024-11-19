/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/19 13:59:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->mlx = NULL;
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

int	main()
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "CUB3D");
	mlx_hook(data.win, 2, (1L<<0), key_hook, &data); //for key press
	mlx_hook(data.win, 17, 0, close_win, &data); //for cross button
	mlx_loop(data.mlx);
	return (0);
}
