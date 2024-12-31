/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:19:29 by welow             #+#    #+#             */
/*   Updated: 2024/12/31 11:32:29 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief check player position in the map and give the position
 * @param data get player struct
 * @note 1. position + 0.5 is to get the center of the block
*/
void	check_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N'
				|| data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'W'
				|| data->map.map[i][j] == 'E')
			{
				data->player.dir = data->map.map[i][j];
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief set direction and camera plane for player
 * @param data get player struct
 * @note 1. if "N" then direction face up and plane x will be 0.6
 * 		 (60 degree) from left
 * 		 2. if "S" then direction face down and plane x will be -0.6
 * 		 (-60 degree) from left
*/
static void	init_north_south(t_data *data)
{
	if (data->player.dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

/**
 * @brief set direction and camera plane for player
 * @param data get player struct
 * @note 1. if "E" then direction face right and plane y will be 0.6
 * 		 (60 degree) from left
 * 		 2. if "S" then direction face down and plane y will be -0.6
 * 		 (-60 degree) from left
*/
static void	init_east_west(t_data *data)
{
	if (data->player.dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

/**
 * @brief initialize player direction
 * @param data get player struct
*/
void	init_player_dir(t_data *data)
{
	init_north_south(data);
	init_east_west(data);
}

void	error_handling2(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east
		|| !map->floor || !map->ceiling || !map->map)
		ft_error("Fail to allocate memory56");
}
