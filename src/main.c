/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/26 13:54:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));

	printf("DEBUG\n");
	printf("mlx: %p\n", data->mlx);
	printf("win: %p\n", data->win);
	printf("win_width: %d\n", data->win_width);
	printf("win_height: %d\n", data->win_height);
	printf("map: %p\n", data->map);

}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac == 2)
		return (printf("Wrong argument"), 1);
	//initialize_data(&data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (data.win == NULL)
		return (1);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_loop(data.mlx);
}
