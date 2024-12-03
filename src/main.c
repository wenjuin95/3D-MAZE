/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 23:11:42 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int	main(int argc, char **argv)
{
	t_arg	arg;

	initialize_arg(&arg);
	parse(argc, argv, &arg);
	 print_arg_struct(&arg);
	free_arg(&arg);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parsing(&data, av) == 1)
		return (1);
	if (initialize_mlx(&data) == 1)
		return (1);
	initialize_texture(&data);
	render_the_image(&data);
	initialize_mlx_hook(&data);
	mlx_loop(data.mlx);
	debuger(&data);
}
