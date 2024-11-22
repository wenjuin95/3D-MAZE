#include "raycasting.h"

bool valid_pos(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->win_width - 1.25)
		return (false);
	if (y < 0.25 || y >= data->win_height - 1.25)
		return (false);
	return true;
}

int validate_move(t_data *data, double new_x, double new_y)
{
	int moved = 0;

	moved = 0;
	if (valid_pos(data, new_x, data->player.pos_y))
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (valid_pos(data, data->player.pos_x, new_y))
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

int replace_img(t_data *data)
{
	data->player.moved += move_player(data);
	if(data->player.moved == 0)
		return 0;
	change_img(data); // not yet implemented
	return (0);
}
