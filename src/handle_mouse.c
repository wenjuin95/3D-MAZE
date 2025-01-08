/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:05 by welow             #+#    #+#             */
/*   Updated: 2025/01/08 15:48:46 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief get the mouse move to a location when it is out of the window
 * @param x the x position of the mouse
 * @param y the y position of the mouse
 * @param data the data
 * @note 1. if mouse is out of edge right, move the mouse to the left
 * @note 2. if mouse is out of edge left, move the mouse to the right
 * @note 3. "mlx_mouse_move" is to move the mouse to the new position
 */
void	get_mouse_pos(int x, int y, t_data *data)
{
	if (x > (WIN_WIDTH / 2))
	{
		x = (WIN_WIDTH / 2);
		mlx_mouse_move(data->mlx, data->win, x, y);
		data->mouse = 1;
	}
	if (x < (WIN_WIDTH / 2))
	{
		x = (WIN_WIDTH / 2);
		mlx_mouse_move(data->mlx, data->win, x, y);
		data->mouse = 1;
	}
}

/**
 * @brief handle the mouse movement
 * @param x the x position of the mouse
 * @param y the y position of the mouse
 * @param data the data
 * @note 1. get the pos_x to different where left or right
*/
int	handle_mouse(int x, int y, t_data *data)
{
	static int	pos_x = WIN_WIDTH / 2;

	get_mouse_pos(x, y, data);
	if (x < pos_x)
		rotate_left(data);
	else if (x > pos_x)
		rotate_right(data);
	return (0);
}
