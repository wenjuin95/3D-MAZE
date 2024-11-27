/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/27 22:03:51 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_width = SCREEN_W;
	data->win_height = SCREEN_H;
	data->texture.tex_size = TEXTURE_SIZE;
}

int	*xpm_to_img(t_data *data, char *path)
{
	t_img	img;
	int		*buffer;
	int		x;
	int		y;

	init_texture(data, path, &img); //tomorrow continue
	buffer = ft_calloc(1, sizeof * buffer
			* data->texture.tex_size * data->texture.tex_size);
	if (buffer == NULL)
		clean_and_exit(data);
	y = 0;
	while (y < data->texture.tex_size)
	{
		x = 0;
		while (x < data->texture.tex_size)
		{
			buffer[y * data->texture.tex_size + x]
				= img.img_addr[y * data->texture.tex_size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, img.img);
	return (buffer);
}

/**
 * @brief initialize the texture for north, south, west, and east
 * @param data the north, south, west, and east texture
 * @return void
 * @note 1. allocate 4 memory for the texture
*/
void	initialize_img(t_data *data)
{
	data->tex = ft_calloc(4, sizeof * data->tex);
	if (data->tex == NULL)
		clean_and_exit(data);
	data->tex[NORTH] = xpm_to_img(data, data->texture.north);
	data->tex[SOUTH] = xpm_to_img(data, data->texture.south);
	data->tex[WEST] = xpm_to_img(data, data->texture.west);
	data->tex[EAST] = xpm_to_img(data, data->texture.east);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (data.win == NULL)
		return (1);
	initialize_img(&data);
	debuger(&data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_loop(data.mlx);
}
