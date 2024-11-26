/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/11/26 10:55:39 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parse.h"

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 1)
		return (ft_error("wrong argument/ without argument"), 1);
	initialize_arg(&arg);
	parse(argc, argv, &arg);
	free_arg(&arg);
	if (arg.map.map_layout != NULL)
		printf("parsing okay\n");
	return (0);
}
