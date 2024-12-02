/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:05 by welow             #+#    #+#             */
/*   Updated: 2024/12/02 16:19:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define MOUSE_SPEED 0

void	wrap_mouse(int x, int y, t_data *data)
{
	if (x > data->win_width - MOUSE_SPEED)
	{
		x = MOUSE_SPEED;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	if (x < MOUSE_SPEED)
	{
		x = data->win_width - MOUSE_SPEED;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
}


int	handle_mouse(int x, int y, t_data *data)
{
	static int pos_x = WIN_WIDTH / 2;

	wrap_mouse(x, y, data);
	if (x == pos_x)
		return (0);
	else if (x < pos_x)
	{
		rotate_left(data);
		printf("move left: %d\n", data->player.mouse_moved);
	}
	else if (x > pos_x)
	{
		rotate_right(data);
		printf("move right: %d\n", data->player.mouse_moved);
	}
	return (0);
}
