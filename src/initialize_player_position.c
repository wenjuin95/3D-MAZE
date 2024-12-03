/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_player_position.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:15:55 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 23:16:06 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_north_south(t_data *data)
{
	if (data->player.dir == 'N')
	{
		//player direction face up
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		//player camera plane from left
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'S')
	{
		//player direction face down
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		//player camera plane from left
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

void	init_east_west(t_data *data)
{
	if (data->player.dir == 'E')
	{
		//player direction face right
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		//player camera plane from left
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.dir == 'W')
	{
		//player direction face left
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		//player camera plane from left
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	init_player_dir(t_data *data)
{
	init_north_south(data);
	init_east_west(data);
}
