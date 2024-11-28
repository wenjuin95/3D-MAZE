/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/28 20:43:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_width = SCREEN_W;
	data->win_height = SCREEN_H;
	data->texture.texture_size = TEXTURE_SIZE;
}

void	initialize_square_texture_pixel(t_data *data)
{
	int	i;

	data->tex_pixel = ft_calloc(data->win_height + 1, sizeof * data->tex_pixel);
	if (data->tex_pixel == NULL)
		clean_and_exit(data);
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pixel[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pixel);
		if (data->tex_pixel[i] == NULL)
			clean_and_exit(data);
		i++;
	}
}

int	raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		 init_ray_info(x, &data->ray, player); //not yet
		 init_dda(&data->ray, player); //not yet
		 perform_dda(&data->ray, data); //not yet
		 calculate_line_height(&data->ray, data, player); //not yet
		 update_texture_pixel(data, &data->texture, &data->ray, x); //not yet
	}
}

void	init_img(t_data *data, t_img *img, int width, int height)
{
	//initialize to all 0 again
	img->img = NULL;
	img->img_addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
	//////////////////////////
	img->img = mlx_new_image(data->mlx, width, height);
	if (img->img == NULL)
		clean_and_exit(data);
	img->img_addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->size_line, &img->endian);

}

void	set_frame_image_pixel(t_data *data, t_img *img, int x, int y)
{
	//if (data->tex_pixel[y][x] > 0)
	//	set_image_pixel(img, x, y, data->tex_pixel[y][x]);
	//else if (y < data->win)
}

void	render_frame(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	init_img(data, &img, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		 while (x < data->win_width)
		 {
			set_frame_image_pixel(data, &img, x, y);//OTW must
			x++;
		 }
		 y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}

void	render_image(t_data *data)
{
	initialize_square_texture_pixel(data);
	raycasting(&data->player, data); //OTW
	render_frame(data); //OTW
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
	render_image(&data);
	debuger(&data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, &data);
	mlx_loop(data.mlx);
}
