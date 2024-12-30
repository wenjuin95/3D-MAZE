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

	//calculate the positoin of the pixel to the address of the image
	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));

	//set the color of the pixel to the address
	*(unsigned int *)dst = color;
}

int main()
{
	void *mlx;
	void *win;
	t_data img;

	//mlx_init is the connection to the display server
	mlx = mlx_init();

	//create a window
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx 42");

	//create an image with the size of the window
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);

	//get the information aboute the image and allow for modification
	//bit_per_pixel mean the number of bits used to represent a pixel color
	// - 32 because a pixel is coded on 4 char, those chars worth 8 bits each, which gives us 32.
	//size_line is the size of a line in bytes
	// - 3200 because the width of one line of pixel is 800, times 4, because a pixel is coded on 4 chars
	//endian is to tell you if the pixel color is stored in little endian or big endian
	// - 0 or 1, depending of the architecture of the computer you use (more informations in the link above).
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);

	//draw
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			my_pixel_put(&img, i, j, 0x00FF00);

	//put image to window
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	//loop to keep the window open
	mlx_loop(mlx);
	return (0);
}
