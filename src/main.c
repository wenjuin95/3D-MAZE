/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/10 00:22:50 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (printf("Wrong argument"), 1);
	initialize_data(&data);
	if (parse(av, &data) == 1)
		return (1);
	debug_parsing(&data);
	// if (initialize_mlx(&data) == 1)
	// 	return (1);
	// initialize_texture(&data);
	// render_the_image(&data);
	// initialize_mlx_hook(&data);
	// mlx_loop(data.mlx);
	// clean_and_exit(&data);
}

// static void print_map_struct(const t_map *map)
// {
//     if (!map)
//       return;
//     printf("Map Layout Length: (%d)\n", map->maply_height);
//     printf("Map Height: (%d)\n", map->map_height);
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
//     if (map->map_layout)
//     {
//         for (int i = 0; map->map_layout[i] != NULL; i++)
//             printf("%s$$\n", map->map_layout[i]);
//     }
//     else
//         printf("  (null)\n");
//     printf("\n\n");
//     printf("Floor Hex: (0x%zx)\n", map->floor_hex);
//     printf("Ceiling Hex: (0x%zx)\n", map->ceiling_hex);
// }

// static void print_arg_struct(const t_arg *arg)
// {
//     if (!arg)
//         return;
//     printf("\033[1;31mPrinting arg struct:\n\n\n\033[0m");
//     printf("Map Address: (%s)\n", arg->map_add ? arg->map_add : "(null)");
//     printf("Map Struct:\n");
//     print_map_struct(&arg->map);
//     printf("printng end\n");
// }

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	if (argc != 2)
// 		return (ft_error("wrong argument!!!"), 1);
// 	initialize_arg(&data);
// 	if (parse(argv, &data) == 1)
//         ft_error("Fail to parse\n");
// 	// print_arg_struct(&data);

//     printf("MAP\n");
//     printf("map_height (int): (%d)\n", data.map.maply_height);
//     printf("map_width (int): (%d)\n", data.map.map_width);
//     printf("map floor_hex (size_t): (#%lx)\n", data.map.floor_hex);
//     printf("map ceiling_hex (size_t): (#%lx)\n", data.map.ceiling_hex);
//     printf("map texture north (char *): (%s)\n", data.map.north);
//     printf("map texture south (char *): (%s)\n", data.map.south);
//     printf("map texture east (char *): (%s)\n", data.map.east);
//     printf("map texture west (char *): (%s)\n", data.map.west);
//     printf("\n");
//     for(int i = 0; data.map.map_layout[i]; i++)
//         printf("(%s)\n", data.map.map_layout[i]);
//     printf("\n");
// 	printf("\nPLAYER\n");
// 	printf("player direction: %c\n", data.player.dir);
// 	printf("player position x: %f\n", data.player.pos_x);
// 	printf("player position y: %f\n", data.player.pos_y);
// 	printf("player direction x: %f\n", data.player.dir_x);
// 	printf("player direction y: %f\n", data.player.dir_y);
// 	printf("end of main\n");
//     free_arg(&data);
// 	return (0);
// }
