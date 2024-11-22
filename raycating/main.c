#include "raycasting.h"

void parse_arg(t_data *data)
{
	data->map = malloc(sizeof(char *) * 10);
	data->map[0] = "111111111111111";
	data->map[1] = "100000000000001";
	data->map[2] = "100000000000001";
	data->map[3] = "100000000000001";
	data->map[4] = "1000000N0000001";
	data->map[5] = "100000000000001";
	data->map[6] = "100000000000001";
	data->map[7] = "100000000000001";
	data->map[8] = "100000000000001";
	data->map[9] = "111111111111111";
	data->map[10] = NULL;
	data->tex.north = "wood.xpm";
	data->tex.south = "wood.xpm";
	data->tex.east = "wood.xpm";
	data->tex.west = "wood.xpm";
	data->tex.floor = set_rgb("138, 138, 138");
	data->tex.ceiling = set_rgb("36, 36, 36");
	data->tex.hex_floor = convert_rgb_to_hex(data->tex.floor);
	data->tex.hex_ceiling = convert_rgb_to_hex(data->tex.ceiling);
	data->player.dir = 'N';
	if (data->player.dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
	else if (data->player.dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else
		return ;
	int i = 0;
	while (data->map[i])
	{
		int j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}

	printf("-----------------DEBUG-----------------\n");
	printf("color floor: #%lx\n", data->tex.hex_floor);
	printf("color ceiling: #%lx\n", data->tex.hex_ceiling);
	printf("texture north: %s\n", data->tex.north);
	printf("texture south: %s\n", data->tex.south);
	printf("texture east: %s\n", data->tex.east);
	printf("texture west: %s\n", data->tex.west);
	printf("Player pos: ");
	printf("x = %f, y = %f\n", data->player.pos_x, data->player.pos_y);
	printf("Player direction: %c ", data->player.dir);
	printf("(x = %f, y = %f)\n", data->player.dir_x, data->player.dir_y);
}

void init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->map = NULL;
	data->texture_pixels = NULL;
	data->texture = NULL;

	data->player.dir = '\0';
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.moved = 0;
	data->player.move_x = 0;
	data->player.move_y = 0;
	data->player.rotate = 0;

	data->tex.north = NULL;
	data->tex.south = NULL;
	data->tex.east = NULL;
	data->tex.west = NULL;
	data->tex.floor = 0;
	data->tex.ceiling = 0;
	data->tex.hex_ceiling = 0x0;
	data->tex.hex_floor = 0x0;
	data->tex.size = BLOCK_SIZE;
	data->tex.step = 0;
	data->tex.pos = 0;
	data->tex.x = 0;
	data->tex.y = 0;

	data->img.img = NULL;
	data->img.addr = NULL;
	data->img.pixel_bits = 0;
	data->img.size_line = 0;
	data->img.endian = 0;
}

int main()
{
	t_data data;
	init_data(&data);
	parse_arg(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "RAYCASTING");
	init_image(&data);
	render_images(&data);
	input_control(&data);
	mlx_loop_hook(data.mlx, replace_img, &data);
	mlx_loop(data.mlx);
}
