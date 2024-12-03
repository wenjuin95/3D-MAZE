/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2024/12/03 13:35:36 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *str)
{
	printf("Error : %s\n", str);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// bool	skip_ispace(char *str)
// {
// 	while (*str != ' ' || *str != '\t' || *str != '\n'
// 			|| *str != '\v' || *str != '\f' || *str != '\r')
// 	{
// 		if (*str == '\0')
// 			return (false);
// 		str++;
// 	}
// 	return (true);
// }
