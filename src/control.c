/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-01 06:00:51 by welow             #+#    #+#             */
/*   Updated: 2024-12-01 06:00:51 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == ESC)
		clean_and_exit(data);
	if (keycode == W && data->player.moved_y == 1) //if player is moving up
		data->player.moved_y = 0; //because it +1 so 0 to stop
	if (keycode == S && data->player.moved_y == -1) //if player is moving down
		data->player.moved_y = 0; //because it -1 so 0 to stop
	if (keycode == A && data->player.moved_x == -1) //if player is moving left
		data->player.moved_x += 1; //because it -1 so +1 to stop
	if (keycode == D && data->player.moved_x == 1) //if player is moving right
		data->player.moved_x -= 1;  //because it +1 so -1 to stop
	if (keycode == LEFT && data->player.rotated <= 1) //if player is rotating left
		data->player.rotated = 0; //because it -1 so 0 to stop
	if (keycode == RIGHT && data->player.rotated >= -1) //if player is rotating right
		data->player.rotated = 0; //because it +1 so 0 to stop
	return (0);
}