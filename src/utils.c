/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2024/11/22 15:14:09 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
# include <stdio.h>

void   ft_error(char *str)
{
    printf("Error : %s\n", str);
    exit(1);
}

void    free_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}