#include "raycasting.h"

void parse_arg(t_data *data)
{
	data->map = malloc(sizeof(char *) * 12);
	if (data->map == NULL) {
        perror("Failed to allocate memory for map");
        exit(EXIT_FAILURE);
    }
	data->map[0] = "111111111111111";
	data->map[1] = "1N0000000000001";
	data->map[2] = "100000000000001";
	data->map[3] = "100000000000001";
	data->map[4] = "100000000010001";
	data->map[5] = "100000000000001";
	data->map[6] = "100000000000001";
	data->map[7] = "100000000000001";
	data->map[8] = "100000000000001";
	data->map[9] = "100000000000001";
	data->map[10] = "111111111111111";
	data->map[11] = "";
	data->tex.north = "wood.xpm";
	data->tex.south = "wood.xpm";
	data->tex.east = "wood.xpm";
	data->tex.west = "wood.xpm";
	data->tex.floor = set_rgb("138, 138, 138"); //set floor color
	data->tex.ceiling = set_rgb("179, 131, 0"); //set ceiling color
	data->tex.hex_floor = convert_rgb_to_hex(data->tex.floor); //convert floor color to hex
	data->tex.hex_ceiling = convert_rgb_to_hex(data->tex.ceiling); //convert ceiling color to hex
	data->player.dir = 'N';

	//set player direction and perpendicular plane
	if (data->player.dir == 'W')
	{

		//this coordinate will point to (x = -1, y = 0)
		data->player.dir_x = -1.0; 
		data->player.dir_y = 0.0;

		//this coordinate will point to (x = 0, y = -0.66) and you also get (x = 0, y = 0.66)
		//it mean a whole vertical line
		//upper side is derived automatically during rendering process
		data->player.plane_x = 0.0;
		data->player.plane_y = -0.66;

		/**
		 * Why Only One Vector is Defined in Your Code
		 * In your code, the camera plane vector (0.66, 0) represents the right side of the camera plane relative to the player's current direction. The left side is derived automatically during the rendering process because it is simply the negative of the right side.
		 * 
		 * How (-0.66, 0) is Derived
		 * For a field of view:
		 * The full camera plane spans symmetrically around the direction vector.
		 * If the right side of the camera plane is (0.66, 0), the left side will be (-0.66, 0) because:
		 * > Left = −1 × Right Vector
		 * So, for (0.66, 0), the opposite side becomes (-0.66, 0).
		 * 
		 * In Raycasting:
		 * When casting rays:
		 * Rays are spread across the full field of view.
		 * The direction of each ray is calculated by interpolating between the two edges of the camera plane:
		 * > Ray Direction = Direction Vector + (Camera Plane Vector × Interpolation Factor)
		 * >> For the left edge, the interpolation factor is -1 (leading to (-0.66, 0)).
		 * >> For the right edge, the interpolation factor is +1 (keeping (0.66, 0)).
		 * 
		 * Code Behavior
		 * Your code specifies the player's view direction (dir_x, dir_y) and the camera plane's right vector. The left side is implicit because it's symmetric and is derived during calculations.
		*/
	}
	else if (data->player.dir == 'E')
	{
		//this coordinate will point to (x = 1, y = 0)
		data->player.dir_x = 1.0;  //set player x direction
		data->player.dir_y = 0.0; //set player y direction

		//this coordinate will point to (x = 0, y = 0.66) and you also get (x = 0, y = -0.66)
		//it mean a whole vertical line
		data->player.plane_x = 0.0; //set player x perpendicular to direction
		data->player.plane_y = 0.66; //set player y perpendicular to direction
		//perpendicular to direction means it is 90 degree to the direction
		//(dir_x, diry_y) is perpendicular to (plane_x, plane_y)
	}
	else if (data->player.dir == 'S')
	{
		//this coordinate will point to (x = 0, y = 1)
		data->player.dir_x = 0.0;
		data->player.dir_y = 1.0;

		//this coordinate will point to (x = -0.66, y = 0) and you also get (x = 0.66, y = 0)
		//it mean a whole horizontal line 
		data->player.plane_x = -0.66;
		data->player.plane_y = 0.0;
	}
	else if (data->player.dir == 'N')
	{
		//this coordinate will point to (x = 0, y = -1)
		data->player.dir_x = 0.0;
		data->player.dir_y = -1.0;

		//this coordinate will point to (x = 0.66, y = 0) and you also get (x = -0.66, y = 0)
		//it mean a whole horizontal line
		data->player.plane_x = 0.66;
		data->player.plane_y = 0.0;
	}
	else
		return ;

	//set player coordinate
	int i = 0;
	while (data->map[i])
	{
		int j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N') //if found player position
			{
				data->player.pos_x = (double)j + 0.5; //"+ 0.5" is to put the player in the middle of the block
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
	data->mlx = NULL; //set mlx
	data->win = NULL; //set window
	data->win_height = WIN_HEIGHT; //set window height
	data->win_width = WIN_WIDTH; //set window width
	data->map = NULL; //set map
	data->texture_pixels = NULL; //set texture pixels
	data->texture = NULL; //set texture

	data->player.dir = '\0'; //set player direction (either N, S, E, W)
	data->player.pos_x = 0; //set player x position
	data->player.pos_y = 0; //set player y position
	data->player.dir_x = 0; //set player x direction (view in x)
	data->player.dir_y = 0; //set player y direction (view in y)
	data->player.plane_x = 0; //set player x plane (view in x but perpendicular to direction)
	data->player.plane_y = 0; // set player y plane (view in y but perpendicular to direction)
	data->player.moved = 0; //set player move flag
	data->player.move_x = 0; //set player move in x direction
	data->player.move_y = 0; //set player move in y direction
	data->player.rotate = 0; //set player rotate

	data->tex.north = NULL; //set north texture
	data->tex.south = NULL; //set south texture
	data->tex.east = NULL; //set east texture
	data->tex.west = NULL; //set west texture
	data->tex.floor = 0; //set floor texture
	data->tex.ceiling = 0; //set ceiling texture
	data->tex.hex_ceiling = 0x0; //set color of the ceiling
	data->tex.hex_floor = 0x0; //set color of the floor
	data->tex.size = BLOCK_SIZE; //set size of the texture
	data->tex.step = 0; //set step of the texture
	data->tex.pos = 0; //set position of the texture
	data->tex.x = 0; //set x position of the texture
	data->tex.y = 0; //set y position of the texture

	data->img.img = NULL; //set image
	data->img.addr = NULL; //set address of the image
	data->img.pixel_bits = 0; //set bits per pixel
	data->img.size_line = 0; //set size of the line
	data->img.endian = 0; //set endian
}

int main()
{
	t_data data;
	init_data(&data); //initialize data
	parse_arg(&data); //parse argument
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "RAYCASTING");
	init_image(&data); //initialize image
	render_images(&data);
	input_control(&data);
	if (mlx_loop_hook(data.mlx, replace_i, &data) == -1)
		printf("Error: loop\n");
	else
		printf("Success: loop\n");
	mlx_loop(data.mlx);
}
