#include "raycasting.h"

//create a 2D array to store the pixels of the texture
static void init_texture_pixels(t_data *data)
{
	data->texture_pixels = ft_calloc(data->win_height + 1, sizeof *data->texture_pixels);
	int i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1, sizeof **data->texture_pixels);
		i++;
	}
}

//initialize ray
void init_ray(t_raycast *raycast)
{
	raycast->camera_x = 0; // x position of the camera
	raycast->dir_x = 0; // x direction of the camera
	raycast->dir_y = 0; // y direction of the camera
	raycast->map_x = 0; // x position of the map
	raycast->map_y = 0; // y position of the map
	raycast->step_x = 0; // x step of the ray
	raycast->step_y = 0; // y step of the ray
	raycast->side_dist_x = 0; // x distance of the side
	raycast->side_dist_y = 0; // y distance of the side
	raycast->delta_dist_x = 0; //delta distance of the x
	raycast->delta_dist_y = 0; //delta distance of the y
	raycast->wall_dis = 0; // distance to the wall
	raycast->wall_x = 0; // x position of the wall
	raycast->side = 0; // side of the wall
	raycast->line_height = 0; // height of the line
	raycast->draw_start = 0; // start of the drawing
	raycast->draw_end = 0; // end of the drawing
}

void init_img(t_data *data, t_img *image, int width, int height)
{
	data->img.img = NULL;
	data->img.addr = NULL;
	data->img.pixel_bits = 0;
	data->img.size_line = 0;
	data->img.endian = 0;
	image->img = mlx_new_image(data->mlx, width, height);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits, &image->size_line, &image->endian);
}

void set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	int pixel;

	if (data->texture_pixels[y][x] > 0) // if the pixel is not empty
	{
		pixel = y * ( image->size_line / 4 ) + x;
		image->addr[pixel] = data->texture_pixels[y][x];
	}
	else if (y < data->win_height / 2) // if the pixel is empty and the y position is less than half of the window height
	{
		pixel = y * ( image->size_line / 4 ) + x;
		image->addr[pixel] = data->tex.hex_ceiling;
	}
	else if (y < data->win_height - 1) // if the pixel is empty and the y position is less than the window height minus 1
	{
		pixel = y * ( image->size_line / 4 ) + x;
		image->addr[pixel] = data->tex.hex_floor;
	}
}

void render_frame(t_data* data)
{
	t_img image;
	int x;
	int y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

void render_images(t_data *data)
{
	init_texture_pixels(data); //initialize texture pixels
	init_ray(&data->raycast); //initialize ray
	raycasting(&data->player, data);
	render_frame(data);
}
