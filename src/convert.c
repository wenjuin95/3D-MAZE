/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:29:46 by chtan             #+#    #+#             */
/*   Updated: 2024/11/22 19:33:10 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/parse.h"

size_t	convert_rgb_to_hex(int *rgb_tab)
{
	size_t	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

static int *copy_to_rgb_array(char **rgb_to_convert, int *rgb)
{
	int i = 0;
	while (rgb_to_convert[i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		i++;
	}
	return (rgb);
}

int *set_rgb(char *line)
{
	char **rgb_to_convert = ft_split(line, ',');
	int count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
		return (0);
	int *rgb = malloc(sizeof(int) * 3);
	return (copy_to_rgb_array(rgb_to_convert, rgb));
}
