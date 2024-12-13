#include "../minilibx-linux/mlx.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_data
{
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

int main()
{
	void *mlx;
	void *win;
	t_data img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx 42");

	//initialize
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);

	//draw
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			my_pixel_put(&img, i, j, 0x00FF00);

	//put image to window
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
