/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/14 10:01:37 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static void print_map_struct(const t_map *map)
// {
//     if (!map)
//       return;
//     printf("Map Layout Length: (%d)\n", map->map_height);
//     printf("Map Height: (%d)\n", map->file_height);
// 	printf("map layout width %d\n", map->map_width);
//     printf("Map Width: \n");
//     printf("North Texture: (%s)\n", map->north ? map->north : "(null)");
//     printf("south Texture: (%s)\n", map->south ? map->south : "(null)");
//     printf("West Texture: (%s)\n", map->west ? map->west : "(null)");
//     printf("East Texture: (%s)\n", map->east ? map->east : "(null)");
//     printf("Sprite: (%s)\n", map->sprite ? map->sprite : "(null)");
//     printf("Floor RGB: ");
//     if (map->floor)
//         printf("(%d), (%d), (%d)\n", map->floor[0], map->floor[1], map->floor[2]);
//     else
//         printf("(null)\n");
//     printf("Ceiling RGB: ");
//     if (map->ceiling)
//     printf("(%d), (%d), (%d)\n", map->ceiling[0], map->ceiling[1],
//         map->ceiling[2]);
//     else
//         printf("(null)\n");
//     printf("Map Layout:\n");
//     if (map->map)
//     {
//         for (int i = 0; map->map[i] != NULL; i++)
//             printf("%s$$\n", map->map[i]);
//     }
//     else
//         printf("  (null)\n");
//     printf("\n\n");
//     printf("Floor Hex: (0x%zx)\n", map->floor_hex);
//     printf("Ceiling Hex: (0x%zx)\n", map->ceiling_hex);
// }

// static void print_arg_struct(t_data *arg)
// {
//     if (!arg)
//         return;
//     printf("\033[1;31mPrinting arg struct:\n\n\n\033[0m");
//     printf("Map Address: (%s)\n", arg->map_add ? arg->map_add : "(null)");
//     printf("Map Struct:\n");
//     print_map_struct(&arg->map);
//     printf("printng end\n");
// }
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parse(av, &data) == 1)
		return (1);
	// print_arg_struct(&data);
	// debug_parsing(&data);
	if (initialize_mlx(&data) == 1)
		return (1);
	initialize_texture(&data);
	render_the_image(&data);
	initialize_mlx_hook(&data);
	mlx_loop(data.mlx);
	clean_and_exit(&data);
}

