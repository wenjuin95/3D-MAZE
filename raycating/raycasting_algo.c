#include "raycasting.h"

static void init_raycast_info(int x, t_raycast *raycast, t_player *player)
{
	init_ray(raycast);
	raycast->camera_x = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
	raycast->dir_x = player->dir_x + player->plane_x * raycast->camera_x; // x direction of the ray
	raycast->dir_y = player->dir_y + player->plane_y * raycast->camera_x; // y direction of the ray
	raycast->map_x = (int)player->pos_x; // x position in the map
	raycast->map_y = (int)player->pos_y; // y position in the map
	raycast->delta_dist_x = fabs(1 / raycast->dir_x); // x distance of the delta
	raycast->delta_dist_y = fabs(1 / raycast->dir_y); // y distance of the delta
}

static void set_dda(t_raycast *raycast, t_player *player)
{
	if (raycast->dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (player->pos_x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - player->pos_x) * raycast->delta_dist_x;
	}
	if (raycast->dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (player->pos_y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - player->pos_y) * raycast->delta_dist_y;
	}
}

static void perform_dda(t_data *data, t_raycast *raycast)
{
	int hit = 0;
	while (hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (raycast->map_y < 0.25 || raycast->map_x < 0.25)
			break ;
		else if (data->map[raycast->map_y][raycast->map_x] == '1')
			hit = 1;
	}
}

static void calculate_line_height(t_raycast *raycast, t_data *data, t_player *player)
{
	if (raycast->side == 0)
		raycast->wall_dis = (raycast->side_dist_x - raycast->delta_dist_x);
	else
		raycast->wall_dis = (raycast->side_dist_y - raycast->delta_dist_y);
	raycast->line_height = (int)(data->win_height / raycast->wall_dis);
	raycast->draw_start = -raycast->line_height / 2 + data->win_height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + data->win_height / 2;
	if (raycast->draw_end >= data->win_height)
		raycast->draw_end = data->win_height - 1;
	if (raycast->side == 0)
		raycast->wall_x = player->pos_y + raycast->wall_dis * raycast->dir_y;
	else
		raycast->wall_x = player->pos_x + raycast->wall_dis * raycast->dir_x;
	raycast->wall_x -= floor(raycast->wall_x);
}

static void get_texture_index(t_data *data, t_raycast *raycast)
{
	if (raycast->side == 0)
	{
		if (raycast->dir_x < 0)
			data->tex.index = WEST;
		else
			data->tex.index = EAST;
	}
	else
	{
		if (raycast->dir_y > 0)
			data->tex.index = SOUTH;
		else
			data->tex.index = NORTH;
	}
}

void update_texture_pixels(t_data *data, t_texture *tex, t_raycast *raycast, int x)
{
	int y;
	int color;

	get_texture_index(data, raycast);
	tex->x = (int)(raycast->wall_x * tex->size);
	if ((raycast->side == 0 && raycast->dir_x < 0) || (raycast->side == 1 && raycast->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / raycast->line_height;
	tex->pos = (raycast->draw_start - data->win_height / 2 + raycast->line_height / 2) * tex->step;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->texture[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}

void raycasting(t_player *player, t_data *data)
{
	t_raycast raycast;
	int x;

	x = 0;
	raycast = data->raycast;
	while (x < data->win_width)
	{
		init_raycast_info(x, &raycast, player);
		set_dda(&raycast, player);
		perform_dda(data, &raycast);
		calculate_line_height(&raycast, data, player);
		update_texture_pixels(data, &data->tex, &raycast, x);
		x++;
	}
}
