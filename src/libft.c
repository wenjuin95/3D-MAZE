/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:20:06 by chtan             #+#    #+#             */
/*   Updated: 2024/12/09 20:20:17 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_strspn(const char *s, const char *accept)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (*s)
    {
        while (accept[i] && *s != accept[i])
            i++;
        if (accept[i] == '\0')
            return (count);
        i = 0;
        count++;
        s++;
    }
    return (count);
}
