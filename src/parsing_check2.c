/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:11:43 by chtan             #+#    #+#             */
/*   Updated: 2024/12/10 14:05:23 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_error("Invalid RGB value"), 1);
		i++;
	}
	return (0);
}

// int	check_top_or_bottom(char **map_tab, int i, int j)
// {
// 	if (!map_tab || !map_tab[i] || !map_tab[i][j])
// 		return (1);
// 	while (map_tab[i][j])
// 	{
// 		if (map_tab[i][j] != '1' && map_tab[i][j] != ' ')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// /**
//  * wanna seperate the check map serounded by wall function into 2
//  * firstly i'll pre sort and set all the space to 1
//  */
// int check_map_closed(t_map *map, int rows)
// {
// 	char **tmp;
// 	int i = 0;
// 	int j = 0;

// 	tmp = copy_2d_array(map->map, 0, rows);
// 	while (i < rows)
// 	{
// 		while (tmp[i][j] != '\0')
// 		{
// 			if (tmp[i] == ' ')
// 				tmp[i][j] = '1';
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (check_top_or_bottom(tmp, 0, 0) == 1
// 		|| check_top_or_bottom(tmp, (rows - 1), 0) == 1)
// 	{
// 		free_2d(tmp);
// 		return (1);
// 	}
// }
