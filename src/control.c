/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:00:51 by welow             #+#    #+#             */
/*   Updated: 2024/12/06 18:18:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief handle the key press event
 * @param keycode the key code
 * @param data the data
 * @note 1. if the key is ESC, close the window
*/
int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_win(data);
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
	if (keycode == MAP)
	{
		if (data->on_map == 1)
			data->on_map = 0;
		else
			data->on_map = 1;
	}
	return (0);
}

/**
 * @brief handle the key release event
 * @param keycode the key code
 * @param data the data
 * @note 1. if the key is ESC, close the window
 * @note 2. if the key is release and player is moving, stop the player
*/
int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_win(data);
	if (keycode == W && data->player.moved_y == 1)
		data->player.moved_y = 0;
	if (keycode == S && data->player.moved_y == -1)
		data->player.moved_y = 0;
	if (keycode == A && data->player.moved_x == -1)
		data->player.moved_x += 1;
	if (keycode == D && data->player.moved_x == 1)
		data->player.moved_x -= 1;
	if (keycode == LEFT && data->player.rotated <= 1)
		data->player.rotated = 0;
	if (keycode == RIGHT && data->player.rotated >= -1)
		data->player.rotated = 0;
	return (0);
}
