/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/31 10:56:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parse(av, &data) == 1)
		return (1);
	if (initialize_mlx(&data) == 1)
		return (1);
	initialize_texture(&data);
	initialize_mlx_hook(&data);
	mlx_loop(data.mlx);
	clean_and_exit(&data);
	return (0);
}
