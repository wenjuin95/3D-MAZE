/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:37:15 by welow             #+#    #+#             */
/*   Updated: 2024/12/03 13:48:31 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void print_map_struct(t_map *map)
{
    if (!map)
      return;
    printf("Map Layout Length: (%d) but (%d)\n", map->mapl_len,
        map->mapl_len - 1);
    printf("Map Height: (%d)\n", map->map_height);
    printf("Map Width: ");
    if (map->map_width)
    {
        for (int i = 0; i < map->mapl_len; i++)
        {
            printf("(%d)", map->map_width[i]);
            if (i < map->mapl_len - 1)
                printf(", ");
        }
        printf("\n");
    }
    else
        printf("(null)\n");
    printf("North Texture: (%s)\n", map->north ? map->north : "(null)");
    printf("South Texture: (%s)\n", map->sout ? map->sout : "(null)");
    printf("West Texture: (%s)\n", map->west ? map->west : "(null)");
    printf("East Texture: (%s)\n", map->east ? map->east : "(null)");
    printf("Sprite: (%s)\n", map->sprite ? map->sprite : "(null)");
    printf("Floor RGB: ");
    if (map->floor)
        printf("(%d), (%d), (%d)\n", map->floor[0], map->floor[1], map->floor[2]);
    else
        printf("(null)\n");
    printf("Ceiling RGB: ");
    if (map->ceiling)
    printf("(%d), (%d), (%d)\n", map->ceiling[0], map->ceiling[1],
        map->ceiling[2]);
    else
        printf("(null)\n");
    printf("Map Layout:\n");
    if (map->map_layout)
    {
        for (int i = 0; map->map_layout[i] != NULL; i++)
            printf("%s", map->map_layout[i]);
    }
    else
        printf("  (null)\n");
    printf("\n\n");
    printf("Floor Hex: (0x%zx)\n", map->floor_hex);
    printf("Ceiling Hex: (0x%zx)\n", map->ceiling_hex);
}

void print_arg_struct(t_data *data)
{
    if (!data)
        return;
    printf("\033[1;31mPrinting data struct:\n\n\n\033[0m");
    printf("Map Address: (%s)\n", data->map_add ? data->map_add : "(null)");
    printf("Map Struct:\n");
    print_map_struct(&data->map);
    printf("printng end\n");
}
