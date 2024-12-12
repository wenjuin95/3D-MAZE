/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2024/12/12 11:39:13 by chtan            ###   ########.fr       */
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
	int	len;

	len = ft_strlen(src);
	if (src[len - 1] == '\n')
		src[len - 1] = '\0';
	return (src);
}

char	**copy_2d_array(char **src, int start, int src_height)
{
	int		j;
	char	**dest;

	j = 0;
	printf("%d\n", start);
	dest = malloc(sizeof(char *) * (src_height - start + 1));
	while (start < src_height)
	{
		dest[j] = ft_strdup(remove_nl(src[start]));
		start++;
		j++;
	}
	free_array((void **)src);
	dest[j] = NULL;
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
