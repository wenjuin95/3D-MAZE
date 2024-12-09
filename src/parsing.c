/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:31:25 by welow             #+#    #+#             */
/*   Updated: 2024/12/08 23:55:10 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void check_player_position(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (ft_strchr("NSEW", data->map[i][j]))
			{
				data->player.dir = data->map[i][j];
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

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

int *set_rgb(char *line)
{
	char **rgb_to_convert = ft_split(line, ',');
	int *rgb = malloc(sizeof(int) * 3);
	int i = 0;
	while (rgb_to_convert[i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		i++;
	}
	free_array((void **)rgb_to_convert);
	return (rgb);
}

size_t	convert_rgb(int *rgb)
{
	size_t result;
	int r;
	int g;
	int b;
	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int parsing(t_data *data, char **file_name)
{
	(void)file_name;
	data->map_height = 10;
	data->map_width = 10;

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (data->map == NULL)
	{
		perror("map memory");
		exit(1);
	}

	//first map
	data->map[0] = ft_strdup("1111111111");
	data->map[1] = ft_strdup("1000000001");
	data->map[2] = ft_strdup("1000000001");
	data->map[3] = ft_strdup("1111001111");
	data->map[4] = ft_strdup("1000000001");
	data->map[5] = ft_strdup("10000S0001");
	data->map[6] = ft_strdup("1000000001");
	data->map[7] = ft_strdup("1000000001");
	data->map[8] = ft_strdup("1000000001");
	data->map[9] = ft_strdup("1111111111");
	data->map[10] = NULL;

	// //second map
	// data->map[0] = ft_strdup("   1111   ");
	// data->map[1] = ft_strdup("   1001   ");
	// data->map[2] = ft_strdup("  100001  ");
	// data->map[3] = ft_strdup("   1001   ");
	// data->map[4] = ft_strdup("1110000111");
	// data->map[5] = ft_strdup("10000S0001");
	// data->map[6] = ft_strdup("1000000001");
	// data->map[7] = ft_strdup("1000000001");
	// data->map[8] = ft_strdup("1000000001");
	// data->map[9] = ft_strdup("1111111111");
	// data->map[10] = NULL;


	data->texture.north = ft_strdup("src/wood.xpm");
	data->texture.south = ft_strdup("src/wood.xpm");
	data->texture.east = ft_strdup("src/wood.xpm");
	data->texture.west = ft_strdup("src/wood.xpm");

	data->texture.floor = set_rgb("138, 138, 138");
	data->texture.ceiling = set_rgb("56, 182, 255");
	data->texture.hex_floor = convert_rgb(data->texture.floor);
	data->texture.hex_ceiling = convert_rgb(data->texture.ceiling);

	check_player_position(data);
	init_player_dir(data);

	debug_parsing(data);

	return (0);
}
