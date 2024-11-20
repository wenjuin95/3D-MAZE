#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK_SIZE 64
# define CHANGE_VIEW 0 // 0 for raycasting, 1 for map view
# define SKY 0x000000
# define FLOOR 0x808080

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define ESC 65307

# define PI 3.14159265359


typedef struct s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool key_turn_left;
	bool key_turn_right;
} t_player;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;

	char *data; // image data
	int bpp; // bits per pixel
	int size_line; // size of line
	int endian; // endian

	t_player player;
	char **map;
}	t_data;

void init_player(t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
int mouse_press(int button, int x, int y, t_player *player);
int mouse_release(int button, int x, int y, t_player *player);
void move_player(t_player *player, t_data *game);
bool player_view(float px, float py, t_data *game);

#endif
