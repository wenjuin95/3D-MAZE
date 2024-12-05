/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2024/12/05 17:22:18 by chtan            ###   ########.fr       */
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

char	*remove_nl(char *src)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(src);
	if (!str)
		ft_error("Fail to allocate memoryabc");
	while (i < ft_strlen(str))
	{
		if (src[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}

char	**copy_2d_array(char **src, int start, int src_height)
{
	int		j;
	char	**dest;

	j = 0;
	dest = malloc(sizeof(char *) * (src_height - start + 1));
	while (start < src_height)
	{
		dest[j] = remove_nl(src[start]);
		start++;
		j++;
	}
	dest[j] = NULL;
	free_2d(src);
	return (dest);
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