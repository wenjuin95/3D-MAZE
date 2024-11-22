#include "raycasting.h"

int key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == W)
		data->player.move_y = 1;
	if (keycode == S)
		data->player.move_y = -1;
	if (keycode == A)
		data->player.move_x = -1;
	if (keycode == D)
		data->player.move_x = 1;
	return 0;
}

int key_release(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == W && data->player.move_y == 1)
		data->player.move_y = 0;
	if (keycode == S && data->player.move_y == -1)
		data->player.move_y = 0;
	if (keycode == A && data->player.move_x == -1)
		data->player.move_x += 1;
	if (keycode == D && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (keycode == LEFT && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (keycode == RIGHT && data->player.rotate >= -1)
		data->player.rotate = 0;
	return 0;
}

int close_win(t_data *data)
{
	(void)data;
	exit(0);
	return 0;
}

void input_control(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 5, close_win, data);
	mlx_loop(data->mlx);
}
