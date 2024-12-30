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

int	button(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int handle_mouse(int x, int y, t_data *data)
{
	//if mouse right near the edge of the screen, move it to the center
	if (x >= WIDTH - 20)
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, y);
	//if mouse left near the edge of the screen, move it to the center
	if (x <= 20)
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
	printf("bits_per_pixel: %d\n", data.bits_per_pixel);
	printf("size_line: %d\n", data.size_line);
	printf("endian: %d\n", data.endian);

	//draw
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			my_pixel_put(&data, i, j, 0x00FF00);

	//mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param): event trigger depending on the function you use
	//win_ptr: window to apply the hook
	//x_event: event to trigger the hook
	//x_mask: mask to trigger the hook
	//funct: function to trigger when the event is triggered
	//param: parameter to pass to the function
	mlx_hook(data.win, DestroyNotify, NoEventMask, close_win, NULL); 	//for close window with X button
	mlx_hook(data.win, KeyPress, KeyPressMask, button, NULL);	//for close window with ESC button
	mlx_hook(data.win, MotionNotify, PointerMotionMask, handle_mouse, &data);	//for mouse move

	//put image to window
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
