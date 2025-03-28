/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 07:51:06 by welow             #+#    #+#             */
/*   Updated: 2024/12/27 12:02:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief move the player forward
 * @param data the data
 * @return 1 if player move, 0 if player not move
*/
int	move_forward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x + (data->player.dir_x * MOVE_SPEED);
	move_y = data->player.pos_y + (data->player.dir_y * MOVE_SPEED);
	return (check_move(data, move_x, move_y));
}

/**
 * @brief move the player backward
 * @param data the data
 * @return 1 if player move, 0 if player not move
*/
int	move_backward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x - (data->player.dir_x * MOVE_SPEED);
	move_y = data->player.pos_y - (data->player.dir_y * MOVE_SPEED);
	return (check_move(data, move_x, move_y));
}

/**
 * @brief move the player left
 * @param data the data
 * @return 1 if player move, 0 if player not move
 * @note 1. move_x :: pos[some nb] + dir[1] so it will move to left chg x pos
 * @note 2. move_y :: pos[some nb] - dir[0] so it will move to left no chg y pos
*/
int	move_left(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x + (data->player.dir_y * MOVE_SPEED);
	move_y = data->player.pos_y - (data->player.dir_x * MOVE_SPEED);
	return (check_move(data, move_x, move_y));
}

/**
 * @brief move the player right
 * @param data the data
 * @return 1 if player move, 0 if player not move
 * @note 1. move_x :: pos[some nb] - dir[1] so it will move to right chg x pos
 * @note 2. move_y :: pos[some nb] + dir[0] so it will move to right no chg y pos
*/
int	move_right(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.pos_x - (data->player.dir_y * MOVE_SPEED);
	move_y = data->player.pos_y + (data->player.dir_x * MOVE_SPEED);
	return (check_move(data, move_x, move_y));
}

/**
 * @brief execute player move when button is pressed
 * @param data the data
 * @return 1 if player move, 0 if player not move
 * @note 1. rotate more then 0 means rotate left (now chg to right)
 * @note 2. rotate less then 0 means rotate right (now chg to left)
*/
int	player_movement(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.moved_y == 1)
		moved = move_forward(data);
	if (data->player.moved_y == -1)
		moved = move_backward(data);
	if (data->player.moved_x == -1)
		moved = move_left(data);
	if (data->player.moved_x == 1)
		moved = move_right(data);
	if (data->player.rotated <= 0)
		moved = rotate_left(data);
	if (data->player.rotated >= 0)
		moved = rotate_right(data);
	return (moved);
}
