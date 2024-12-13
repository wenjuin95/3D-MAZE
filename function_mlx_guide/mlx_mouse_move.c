#include "../minilibx-linux/mlx.h"
#include <X11/X.h> //for key_hook
#include <stddef.h> //for NULL
#include <stdlib.h> //for exit
#include <stdio.h> //for printf

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int size_line;
	int endian;
} t_data;

void my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_win(void *data)
{
	(void)data;
	exit(0);
}

int handle_mouse(int x, int y, t_data *data)
{
	if (x >= WIDTH - 20)
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, y);
	return (0);
}

int main()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "mlx 42");

	//initialize
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.size_line, &data.endian);

	//draw
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			my_pixel_put(&data, i, j, 0x00FF00);

	//for close window
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, NULL);

	mlx_hook(data.win, MotionNotify, PointerMotionMask, handle_mouse, &data);

	//put image to window
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
