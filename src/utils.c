/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2024/12/05 13:24:05 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

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

size_t	ft_len(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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