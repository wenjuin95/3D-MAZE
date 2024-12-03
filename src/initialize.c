/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:24:56 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 13:35:07 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	initialize_map(t_map *map)
{
	if (!map)
		return ;
	ft_bzero(map, sizeof(t_map));
}

void	initialize_arg(t_arg *arg)
{
	if (!arg)
		return ;
	initialize_map(&arg->map);
}
