/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:56:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/18 13:19:37 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//void	debuger(t_data *data)
//{
//	debug_data(data);
//	debug_image(&data->img);
//	debug_texture(&data->texture);
//	debug_raycast(&data->ray);
//	debug_player(&data->player);
//	debug_parsing(data);
//}

//void	debug_data(t_data *data)
//{
//	printf("DEBUG MAIN DATA\n");
//	printf("mlx: %p\n", data->mlx);
//	printf("win: %p\n", data->win);
//	printf("win_width: %d\n", data->win_width);
//	printf("win_height: %d\n", data->win_height);
//}

//void	debug_map(t_minimap *minimap)
//{
//	printf("\nDEBUG MINIMAP DATA\n");
//	printf("image size: %d\n", minimap->view_distance);
//	printf("square size (w x h): %d\n", minimap->size);
//	printf("texture_size: %d\n", minimap->texture_size);
//	printf("offset_x: %d\n", minimap->visible_x);
//	printf("offset_y: %d\n", minimap->visible_y);
//    for (int i = 0; i < minimap->size; i++) {
//        for (int j = 0; j < minimap->size; j++) {
//            printf("%c", minimap->map[i][j]);
//        }
//        printf("\n");
//    }
//}

//void	debug_image(t_img *img)
//{
//	printf("\nDEBUG IMG DATA\n");
//	printf("img: %p\n", img->img);
//	printf("addr: %p\n", img->img_addr);
//	printf("bit per pixel: %d\n", img->pixel_bits);
//	printf("line size: %d\n", img->size_line);
//	printf("endian: %d\n", img->endian);
//}

//void	debug_texture(t_tex *texture)
//{
//	printf("\nDEBUG TEXTURE DATA\n");
//	printf("tex_size: %d\n", texture->texture_size);
//	printf("tex_index: %d\n", texture->texture_index);
//	printf("step: %f\n", texture->step);
//	printf("position: %f\n", texture->position);
//	printf("tex_x: %d\n", texture->tex_x);
//	printf("tex_y: %d\n", texture->tex_y);
//}

//void	debug_raycast(t_raycast *ray)
//{
//	system("clear");
//	printf("\nDEBUG RAYCAST DATA\n");
//	printf("camera: %f\n", ray->camera);
//	printf("map_x: %d\n", ray->map_x);
//	printf("map_y: %d\n", ray->map_y);
//	printf("dir_x: %f\n", ray->dir_x);
//	printf("dir_y: %f\n", ray->dir_y);
//	printf("step_x: %d\n", ray->step_x);
//	printf("step_y: %d\n", ray->step_y);
//	printf("side_dist_x: %f\n", ray->side_dist_x);
//	printf("side_dist_y: %f\n", ray->side_dist_y);
//	printf("delta_dist_x: %f\n", ray->delta_dist_x);
//	printf("delta_dist_y: %f\n", ray->delta_dist_y);
//	printf("wall_dis: %f\n", ray->wall_dis);
//	printf("wall_x: %f\n", ray->wall_x);
//	printf("side: %d\n", ray->side);
//	printf("line_height: %d\n", ray->line_height);
//	printf("draw_start: %d\n", ray->draw_start);
//	printf("draw_end: %d\n", ray->draw_end);
//}

//void	debug_player(t_player *player)
//{
//	printf("\nDEBUG PLAYER DATA\n");
//	printf("player direction: %c\n", player->dir);
//	printf("position x: %f\n", player->pos_x);
//	printf("position y: %f\n", player->pos_y);
//	printf("diraction x: %f\n", player->dir_x);
//	printf("diraction y: %f\n", player->dir_y);
//	printf("camera plane x: %f\n", player->plane_x);
//	printf("camera plane y: %f\n", player->plane_y);
//	printf("player moved_x: %d\n", player->moved_x);
//	printf("player moved_y: %d\n", player->moved_y);
//	printf("player rotate: %d\n", player->rotated);
//}

//void	debug_parsing(t_data *data)
//{
//	printf("MAP\n");
//    printf("map_height (int): (%d)\n", data->map.maply_height);
//    printf("map_width (int): (%d)\n", data->map.map_width);
//    printf("map floor_hex (size_t): (#%lx)\n", data->map.floor_hex);
//    printf("map ceiling_hex (size_t): (#%lx)\n", data->map.ceiling_hex);
//    printf("map texture north (char *): (%s)\n", data->map.north);
//    printf("map texture south (char *): (%s)\n", data->map.south);
//    printf("map texture east (char *): (%s)\n", data->map.east);
//    printf("map texture west (char *): (%s)\n", data->map.west);
//    printf("\n");
//    for(int i = 0; data->map.map_layout[i]; i++)
//        printf("(%s)\n", data->map.map_layout[i]);
//    printf("\n");
//	printf("\nPLAYER\n");
//	printf("player direction: %c\n", data->player.dir);
//	printf("player position x: %f\n", data->player.pos_x);
//	printf("player position y: %f\n", data->player.pos_y);
//	printf("player direction x: %f\n", data->player.dir_x);
//	printf("player direction y: %f\n", data->player.dir_y);
//}
