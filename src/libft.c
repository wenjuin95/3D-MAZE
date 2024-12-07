/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:20:06 by chtan             #+#    #+#             */
/*   Updated: 2024/12/07 12:20:45 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

#include <stddef.h>

int	ft_strspn(const char *s, const char *accept)
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