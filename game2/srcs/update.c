/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:19:01 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/11 21:25:22 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_global *global)
{
	(void) global;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		move_position(global, key);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_viewpoint(global, key);
	else if (key == KEY_ESC)
		exit_program(global);
	return (0);
}

int	update(t_global *global)
{
	(void )global;
	draw_background(global);
	raycasting(global);
	draw(global);
	return (0);
}
