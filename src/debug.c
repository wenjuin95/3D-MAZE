/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:56:11 by welow             #+#    #+#             */
/*   Updated: 2024/12/02 13:35:09 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include	"../include/cub3d.h"

void	debuger(t_data *data)
{
	printf("DEBUG MAIN DATA\n");
	printf("mlx: %p\n", data->mlx);
	printf("win: %p\n", data->win);
	printf("win_width: %d\n", data->win_width);
	printf("win_height: %d\n", data->win_height);

	printf("\nDEBUG IMG DATA\n");
	printf("img: %p\n", data->img.img);
	printf("addr: %p\n", data->img.img_addr);
	printf("bit per pixel: %d\n", data->img.pixel_bits);
	printf("line size: %d\n", data->img.size_line);
	printf("endian: %d\n", data->img.endian);

	printf("\nDEBUG TEXTURE DATA\n");
	printf("NORTH: %s\n", data->texture.north);
	printf("SOUTH: %s\n", data->texture.south);
	printf("EAST: %s\n", data->texture.east);
	printf("WEST: %s\n", data->texture.west);
	printf("floor: %p\n", data->texture.floor);
	printf("ceiling: %p\n", data->texture.ceiling);
	printf("hex_floor: %zu\n", data->texture.hex_floor);
	printf("hex_ceiling: %zu\n", data->texture.hex_ceiling);
	printf("tex_size: %d\n", data->texture.texture_size);
	printf("tex_index: %d\n", data->texture.texture_index);
	printf("step: %f\n", data->texture.step);
	printf("position: %f\n", data->texture.position);
	printf("tex_x: %d\n", data->texture.tex_x);
	printf("tex_y: %d\n", data->texture.tex_y);

	printf("\nDEBUG RAYCAST DATA\n");
	printf("camera: %f\n", data->ray.camera);
	printf("map_x: %d\n", data->ray.map_x);
	printf("map_y: %d\n", data->ray.map_y);
	printf("dir_x: %f\n", data->ray.dir_x);
	printf("dir_y: %f\n", data->ray.dir_y);
	printf("step_x: %d\n", data->ray.step_x);
	printf("step_y: %d\n", data->ray.step_y);
	printf("side_dist_x: %f\n", data->ray.side_dist_x);
	printf("side_dist_y: %f\n", data->ray.side_dist_y);
	printf("delta_dist_x: %f\n", data->ray.delta_dist_x);
	printf("delta_dist_y: %f\n", data->ray.delta_dist_y);
	printf("wall_dis: %f\n", data->ray.wall_dis);
	printf("wall_x: %f\n", data->ray.wall_x);
	printf("side: %d\n", data->ray.side);
	printf("line_height: %d\n", data->ray.line_height);
	printf("draw_start: %d\n", data->ray.draw_start);
	printf("draw_end: %d\n", data->ray.draw_end);

	printf("\nDEBUG PLAYER DATA\n");
	printf("player direction: %c\n", data->player.dir);
	printf("position x: %f\n", data->player.pos_x);
	printf("position y: %f\n", data->player.pos_y);
	printf("diraction x: %f\n", data->player.dir_x);
	printf("diraction y: %f\n", data->player.dir_y);
	printf("camera plane x: %f\n", data->player.plane_x);
	printf("camera plane y: %f\n", data->player.plane_y);
	printf("player moved_x: %d\n", data->player.moved_x);
	printf("player moved_y: %d\n", data->player.moved_y);
	printf("player rotate: %d\n", data->player.rotated);
}

void debug_parsing(t_data *data)
{
	printf("MAP\n");
	printf("map_height: %d\n", data->map_height);
	printf("map_width: %d\n", data->map_width);
	printf("map floor: #%lx\n", data->texture.hex_floor);
	printf("map ceiling: #%lx\n", data->texture.hex_ceiling);
	printf("map texture north: %s\n", data->texture.north);
	printf("map texture south: %s\n", data->texture.south);
	printf("map texture east: %s\n", data->texture.east);
	printf("map texture west: %s\n", data->texture.west);
	printf("\n");
	for(int i = 0; data->map[i]; i++)
		printf("%s\n", data->map[i]);
	printf("\n");

	printf("\nPLAYER\n");
	printf("player direction: %c\n", data->player.dir);
	printf("player position x: %f\n", data->player.pos_x);
	printf("player position y: %f\n", data->player.pos_y);
	printf("player direction x: %f\n", data->player.dir_x);
	printf("player direction y: %f\n", data->player.dir_y);


}
