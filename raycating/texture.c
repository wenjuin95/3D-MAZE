#include "raycasting.h"

static void init_texture_img(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, &data->tex.size, &data->tex.size);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, &img->size_line, &img->endian);
}

static int *xpm_to_img(t_data *data, char *path)
{
	t_img tmp;
	int *buffer;
	int x;
	int y;

	init_texture_img(data, &tmp, path);

	//convert the image to a buffer of pixel data
	buffer = ft_calloc(1, sizeof * buffer * data->tex.size * data->tex.size);
	y = 0;
	while (y < data-> tex.size)
	{
		x = 0;
		while (x < data->tex.size)
		{
			buffer[y * data->tex.size + x] = tmp.addr[y * data->tex.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

// Function to print the texture
void print_texture(int *texture, int size) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            printf("%d ", texture[y * size + x]);
        }
        printf("\n");
    }
}

void init_image(t_data *data)
{
	data->texture = ft_calloc(5, sizeof * data->texture);
	data->texture[NORTH] = xpm_to_img(data, data->tex.north);
	data->texture[SOUTH] = xpm_to_img(data, data->tex.south);
	data->texture[EAST] = xpm_to_img(data, data->tex.east);
	data->texture[WEST] = xpm_to_img(data, data->tex.west);
	// printf("--------------DEBUG TEXTURE--------------\n");
	// printf("texture[NORTH]: ");
	// print_texture(data->texture[NORTH], data->tex.size);
	// printf("texture[SOUTH]: ");
	// print_texture(data->texture[SOUTH], data->tex.size);
	// printf("texture[EAST]: ");
	// print_texture(data->texture[EAST], data->tex.size);
	// printf("texture[WEST]: ");
	// print_texture(data->texture[WEST], data->tex.size);
}
