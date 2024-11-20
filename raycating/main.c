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
 * @brief clear the image
 * @param game the game structure
 */
void clear_image(t_data *game)
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

char **get_map()
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111";
	map[1] = "100000000001";
	map[2] = "100000000101";
	map[3] = "101000000001";
	map[4] = "100000000001";
	map[5] = "100010000001";
	map[6] = "100000000001";
	map[7] = "100100000001";
	map[8] = "100000000001";
	map[9] = "111111111111";
	map[10] = NULL;
	return (map);
}

/**
 * @brief initialize the game
 * @param game the game structure
 */
void init(t_data *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RAYCASTING");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian); //function to get the image data
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/**
 * @brief check if the player view touch the wall
 * @param px the x position of the player view
 * @param py the y position of the player view
 * @param game the game structure
 * @return true if the player view touch the wall, false if the player view doesn't touch the wall
 */
bool touch(float px, float py, t_data *game)
{
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

/**
 *@brief view line from player
 *@param player the player structure
 *@param game the game structure
 *@param start_x the start angle of the line
 *@note 1. if "touch" function return false, draw the pixel
 */
void draw_line( t_player *player, t_data *game, float start_x)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;
	while (touch(ray_x, ray_y, game) == false)
	{
		put_pixel(ray_x, ray_y, 0xFFFFFF, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

/**
 * @brief to move the square in the window
 * @param game the game structure
 * @return 0 is required by mlx_loop_hook
 */
int draw_loop(t_data *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 10, 0xFF0000, game);
	draw_map(game);

	float fraction = PI / 3 / WIDTH; //the angle of the player view
	float start_x = player->angle - PI / 6; //the start angle of the player view
	int i = 0;
	while ( i < WIDTH)
	{
		draw_line(player, game, start_x); //draw the line from the player view
		start_x += fraction;
		i++;
	}


	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main()
{
	t_data game;
	init(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game); //this function will keep calling the draw_loop function
	mlx_loop(game.mlx);

	return (0);
}
