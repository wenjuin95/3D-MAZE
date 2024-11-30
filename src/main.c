/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/30 00:18:38 by welow            ###   ########.fr       */
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

//////////////////////////////////////////////////////////////////////////////////

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
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
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_key_press, &data); //not yet
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_key_release, &data); //not yet
	mlx_loop_hook(data.mlx, rendering, &data); //not yet
	mlx_loop(data.mlx);
}
