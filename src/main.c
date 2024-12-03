/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 13:37:11 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 1)
		return (ft_error("wrong argument/ without argument"), 1);
	initialize_arg(&arg);
	parse(argc, argv, &arg);
	 print_arg_struct(&arg);
    // if (arg.map.map_layout == NULL)
    //     printf("parsing okay\n");
	free_arg(&arg);
	return (0);
}
