#include "raycasting.h"

/**
 * @brief put the pixel in the window
 * @param x the x position of the pixel
 * @param y the y position of the pixel
 * @param color the color of the pixel
 * @param game the game structure
 */
void put_pixel(int x, int y, int color, t_data *game)
{
	if ( x >= WIDTH || y >= HEIGHT || x < 0 || y < 0) //if the pixel is not out of the window
		return ;
	int index = y * game->size_line + x * game->bpp / 8; // calculate the position for pixel color data should be stored
	/*
		these info from the mlx_get_data_addr function
		size_line : the size of a line in bytes
		bpp : the number of bits per pixel
	*/
	game->data[index] = color & 0xFF; //get the red color of the pixel
	game->data[index + 1] = (color >> 8) & 0xFF; //get the green color of the pixel
	game->data[index + 2] = (color >> 16) & 0xFF; //get the blue color of the pixel
	/*
		EXAMPLE:
		color = 0x00FF00
		0x00FF00 & 0xFF = 0x00
		(0x00FF00 >> 8) & 0xFF = 0xFF
		(0x00FF00 >> 16) & 0xFF = 0x00
		so the pixel color is green
	*/
}

/**
 *	@brief draw a square in the window
 *	@param x the x position of the square
 *	@param y the y position of the square
 *	@param size the size of the square
 *	@param color the color of the square
 *	@param game the game structure
 */
void draw_square(int x, int y, int size, int color, t_data *game)
{
	int i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game); //draw the top line of the square
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game); //draw the left line of the square
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game); //draw the right line of the square
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game); //draw the bottom line of the square
		i++;
	}
}

void draw_grid(t_data *game)
{
	char **map = game->map;
	int color = 0x666666;
	int y = 0;
	while(map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, game);
			x++;
		}
		y++;
	}
}

/**
 * @brief draw the map
 * @param game the game structure
 * @note 1. if the map[y][x] is '1', draw the square
 */
void draw_map(t_data *game)
{
	char **map = game->map;
	int color = 0x0000FF;
	int y = 0;
	while(map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, game);
			x++;
		}
		y++;
	}
}

/**
 * @brief overwrite the trail with black color
 * @param game the game structure
 */
void clear_trail(t_data *game)
{
	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game); //clear the pixel
			x++;
		}
		y++;
	}
}

/**
 * @brief get the map
*/
char **get_map()
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111";
	map[1] = "100000000001";
	map[2] = "100000000101";
	map[3] = "100000000001";
	map[4] = "100000000001";
	map[5] = "100010000001";
	map[6] = "100001000001";
	map[7] = "100100100001";
	map[8] = "100000000001";
	map[9] = "111111111111";
	map[10] = NULL;
	return (map);
}

/**
 * @brief draw the background
 * @param game the game structure
 */
void draw_background(t_data *game)
{
    int x, y;
	int color;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
				color = SKY;
			else
				color = FLOOR;
            put_pixel(x, y, color, game);
        }
    }
}


/**
 * @brief check if the player view touch the wall
 * @param px the x position of the player view
 * @param py the y position of the player view
 * @param game the game structure
 * @return true if the player view touch the wall, false if the player view doesn't touch the wall
 */
bool player_view(float px, float py, t_data *game)
{
	// //this for window size
	// (void)game;
	 if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
	 	return (true);

	//this for map size
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

/**
 * @brief calculate the distance between two point (for view)
 * @param x1 the x position of the first point
 * @param y1 the y position of the first point
 * @return the distance between two point view
 */
float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/**
 * @brief calculate the distance between two point (remove fish eye effect)
 * @param x1 the x position of the first point
 * @param y1 the y position of the first point
 * @param x2 the x position of the second point
 * @param y2 the y position of the second point
 * @param game the game structure
 * @return the distance between two point view
 */
float fixed_distance(float x1, float y1, float x2, float y2, t_data *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}

/**
 *@brief view line from player
 *@param player the player structure
 *@param game the game structure
 *@param start_x the start angle of the line
 *@note 1. if "touch" function return false, draw the pixel
 */
void draw_player_view( t_player *player, t_data *game, float start_x, int i)
{
	printf("\nori angle: %f\n", start_x);
	float cos_angle = cos(start_x); //
	printf("cos_angle: %f\n", cos_angle);
	float sin_angle = sin(start_x); //next y cordination length
	printf("sin_angle: %f\n", sin_angle);
	float coordinate_x = player->x; //start x cordination
	printf("coordinate_x: %f\n", coordinate_x);
	float coordinate_y = player->y; //start y cordination
	printf("coordinate_y: %f\n\n", coordinate_y);
	while (player_view(coordinate_x, coordinate_y, game) == false) //if the ray not touch the wall
	{
		if (CHANGE_VIEW == 1)
			put_pixel(coordinate_x, coordinate_y, 0x00FF00, game); //keep drawing the ray
		coordinate_x += cos_angle; //move x cordinate to the next pixel
		coordinate_y += sin_angle; //move y cordinate to the next pixel
	}
	if (CHANGE_VIEW == 0)
	{
		// float dis = distance(coordinate_x - player->x, coordinate_y - player->y); //this cuse fish eye effect
		float dis = fixed_distance(player->x, player->y, coordinate_x, coordinate_y, game); //this fix the fish eye effect
		float height = (BLOCK_SIZE / dis) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 0x0000FF, game);
			start_y++;
		}
	}
}

/**
 * @brief to move the square in the window (in 2d)
 * @param game the game structure
 * @return 0 is required by mlx_loop_hook
 */
int draw_loop(t_data *game)
{
	t_player *player = &game->player;
	move_player(player, game);
	clear_trail(game);
	if (CHANGE_VIEW == 0)
		draw_background(game);
	if (CHANGE_VIEW) //in 2d
	{
		draw_square(player->x, player->y, 10, 0xFF0000, game);
		draw_grid(game);
		draw_map(game);
	}

	//this for draw a line player view (in 2d)
	//draw_player_view(player, game, player->angle, 0);

	 //this for draw a player view (in 3d)
	 float fraction = ((PI / 3) / WIDTH) * 1; //calculate how much angle per line
	 //"PI / 3" is the angle of the triangle view
	 // "WIDTH" is the number of line to draw
	// printf("\nfraction: %f\n", fraction);
	 float start_x = player->angle - (PI / 6); // calculate where the field of view starts (the leftmost ray).
	 // "PI / 6" is the half of the triangle view (30 degree)
	 // "player->angle" is the player angle
	// printf("start_x: %f\n\n", start_x);
	 int i = 0;
	 while (i < WIDTH)
	 {
	 	draw_player_view(player, game, start_x, i); //draw the line from the player view
	 	start_x += fraction ; //move to the next angle line
	 	i+= 1; //move to the next line
	 }

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

/**
 * @brief initialize the game
 * @param game the game structure
 */
void init(t_data *game)
{
	game->mlx = mlx_init(); //initialize the mlx pointer
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RAYCASTING"); //create window
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT); //create a new image for window
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian); //function to get the image data
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0); //put the image to the window
	init_player(&game->player);
	game->map = get_map(); //initialize the map
}

int main()
{
	t_data game;
	init(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_mouse_move(game.mlx, game.win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(game.mlx, draw_loop, &game); //this function will keep calling the draw_loop function
	mlx_loop(game.mlx);

	return (0);
}
