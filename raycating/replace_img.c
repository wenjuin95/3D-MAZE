#include "raycasting.h"


bool valid_pos(t_data *data, double x, double y)
{
	int map_x = x;
	int map_y = y;
	if (data->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

int validate_move(t_data *data, double new_x, double new_y)
{
	int moved;

	moved = 0;

	if (valid_pos(data, new_x, data->player.pos_y) == false)
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (valid_pos(data, data->player.pos_x, new_y) == false)
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

int move_forward(t_data *data)
{
	double new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	double new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_x * MOVE_SPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_x * MOVE_SPEED;
	return (validate_move(data, new_x, new_y));
}

int rotate_left_right(t_data *data, double rotate_speed)
{
	t_player *p;
	double tmp_x;

	p = &data->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotate_speed) - p->dir_y * sin(rotate_speed);
	p->dir_y = tmp_x * sin(rotate_speed) + p->dir_y * cos(rotate_speed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotate_speed) - p->plane_y * sin(rotate_speed);
	p->plane_y = tmp_x * sin(rotate_speed) + p->plane_y * cos(rotate_speed);
	return (1);
}

static int rotate_player(t_data *data, double rotate_dir)
{
	int moved;
	double rotate_speed;

	moved = 0;
	rotate_speed = ROT_SPEED * rotate_dir;
	moved += rotate_left_right(data, rotate_speed);
	return (moved);
}

int move_player(t_data *data)
{
	int moved = 0;
	if (data->player.move_y == 1)
		moved += move_forward(data);
	if (data->player.move_y == -1)
		moved += move_backward(data);
	if (data->player.move_x == -1)
		moved += move_left(data);
	if (data->player.move_x == 1)
		moved += move_right(data);
	if (data->player.rotate != 0)
		moved += rotate_player(data, data->player.rotate);
	return (moved);
}

/**********************************************************************************/

void free_tab(void **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void init_texture_pixel(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->texture_pixels);
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture_pixels);
		i++;
	}
}

static void set_image_pixel(t_img *img, int x, int y, int color)
{
	int dst;

	dst = y * (img->size_line / 4) + x;
	img->addr[dst] = color;
}

static void render_frame(t_data *data)
{
	t_img image;
	int x;
	int y;

	image.img = NULL;
	image.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits, &image.size_line, &image.endian);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (data->texture_pixels[y][x] > 0)
				set_image_pixel(&image, x, y, data->texture_pixels[y][x]);
			else if (y < data->win_height / 2)
				set_image_pixel(&image, x, y, data->tex.hex_ceiling);
			else if (y < data->win_height - 1)
				set_image_pixel(&image, x, y, data->tex.hex_floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}


/**********************************************************************************/

void render_raycast(t_data *data)
{
	init_texture_pixel(data);
	init_ray(&data->raycast);
	raycasting(&data->player, data);
	render_frame(data);
}

void change_img(t_data *data)
{
	render_raycast(data);
}

int replace_i(t_data *data)
{
	data->player.moved += move_player(data);
	if(data->player.moved == 0)
		return 0;
	change_img(data); // not yet implemented
	return (0);
}
