/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:59:52 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:59:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	calculate the length of a string
*	@param	str :: the string to calculate
*	@return	the length of the string
*/
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char *str = "hello";
//     printf("%d",ft_strlen(str));
//     printf("%ld", strlen(str));
// }