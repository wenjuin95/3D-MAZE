/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2025/01/08 15:30:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_img	img;

	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parse(av, &data) == 1)
		return (1);
	if (initialize_mlx(&data) == 1)
		return (1);
	initialize_texture(&data);
	initialize_image(&data, &img, data.win_width, data.win_height);
	data.img = img;
	initialize_mlx_hook(&data);
	mlx_loop(data.mlx);
	clean_and_exit(&data);
	return (0);
}
