/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:05 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 11:09:28 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_mouse_pos(int x, int y, t_data *data)
{
	if (x > data->win_width - (WIN_WIDTH / 2))
	{
		x = (WIN_WIDTH / 2);
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	if (x < (WIN_WIDTH / 2))
	{
		x = data->win_width - (WIN_WIDTH / 2);
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
}


int	handle_mouse(int x, int y, t_data *data)
{
	static int	pos_x = WIN_WIDTH / 2;

	get_mouse_pos(x, y, data);
	if (x == pos_x)
		return (0);
	else if (x < pos_x)
		rotate_left(data);
	else if (x > pos_x)
		rotate_right(data);
	return (0);
}
