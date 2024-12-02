/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 07:51:06 by welow             #+#    #+#             */
/*   Updated: 2024/12/02 11:09:32 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Check if the player is moving to a valid position
 * @param data The data structure
 * @param move_x The x position
 * @param move_y The y position
 * @return true if the position is valid, false is not
 */
bool	valid_position(t_data *data, double move_x, double move_y)
{
	if (data->map[(int)move_y][(int)move_x] == '1')
		return (true);
	return (false);
}

int	check_move(t_data *data, double move_x, double move_y)
{
	int	moved;

	moved = 0;
	if (valid_position(data, move_x, data->player.pos_y) == false)
	{
		data->player.pos_x = move_x;
		moved = 1;
	}
	if (valid_position(data, data->player.pos_x, move_y) == false)
	{
		data->player.pos_y = move_y;
		moved = 1;
	}
	return (moved);
}

int	move_forward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	move_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	return (check_move(data, move_x, move_y));
}

int	move_backward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	move_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	return (check_move(data, move_x, move_y));
}

int	move_left(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x + data->player.dir_y * MOVE_SPEED;
	move_y = data->player.pos_y - data->player.dir_x * MOVE_SPEED;
	return (check_move(data, move_x, move_y));
}

int	move_right(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x - data->player.dir_y * MOVE_SPEED;
	move_y = data->player.pos_y + data->player.dir_x * MOVE_SPEED;
	return (check_move(data, move_x, move_y));
}

int	rotate_left(t_data *data)
{
	double	tmp_x;

	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROTATE_SPEED)
		- data->player.dir_y * sin(ROTATE_SPEED);
	data->player.dir_y = tmp_x * sin(ROTATE_SPEED) + data->player.dir_y
		* cos(ROTATE_SPEED);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROTATE_SPEED)
		- data->player.plane_y * sin(ROTATE_SPEED);
	data->player.plane_y = tmp_x * sin(ROTATE_SPEED) + data->player.plane_y
		* cos(ROTATE_SPEED);
	return (1);
}

int	rotate_right(t_data *data)
{
	double	tmp_x;

	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROTATE_SPEED)
		- data->player.dir_y * sin(-ROTATE_SPEED);
	data->player.dir_y = tmp_x * sin(-ROTATE_SPEED) + data->player.dir_y
		* cos(-ROTATE_SPEED);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROTATE_SPEED)
		- data->player.plane_y * sin(-ROTATE_SPEED);
	data->player.plane_y = tmp_x * sin(-ROTATE_SPEED) + data->player.plane_y
		* cos(-ROTATE_SPEED);
	return (1);
}

int	player_movement(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.moved_y == 1)
		moved += move_forward(data);
	if (data->player.moved_y == -1)
		moved += move_backward(data);
	if (data->player.moved_x == -1)
		moved += move_left(data);
	if (data->player.moved_x == 1)
		moved += move_right(data);
	//if (data->player.rotated != 0)
	//	moved += rotate_player(data, data->player.rotated);
	if (data->player.rotated >= 0) //if rotate number more than 0
		moved += rotate_left(data);
	if (data->player.rotated <= 0) //if rotate number less than 0
		moved += rotate_right(data);
	return (moved);
}

int	rendering(t_data *data)
{
	data->player.moved += player_movement(data); //if player move the moved
	if (data->player.moved == 0)
		return (0);
	render_image(data);
	return (0);
}
