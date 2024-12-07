/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:40:35 by chtan             #+#    #+#             */
/*   Updated: 2024/12/07 11:41:04 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

char	*cut_first3(char *s, int len, int start)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * (len - start + 1));
	while (i < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
