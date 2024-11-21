#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define BLOCK_SIZE 64

# define MOVE_SPEED 5
# define ROT_SPEED 0.03

# define MAP_PIXEL_SIZE 128
# define MAP_VIEW_DIS 4
# define MAP_COLOR_PLAYER 0x00FF00 // Green
# define MAP_COLOR_WALL 0x808080 // Gray
# define MAP_COLOR_FLOOR 0xE6E6E6 // Light Gray
# define MAP_COLOR_CEILING 0x404040 // Dark Gray

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE =4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_img
{
	void *img; // image
	int *addr; // address of the image
	int pixel_bits; // bits per pixel
	int size_line; // size of the line
	int endian; // endian
}	t_img;

typedef struct s_texture
{

	char *north; // path to the north texture
	char *south; // path to the south texture
	char *east; // path to the east texture
	char *west; // path to the west texture
	int *floor; // floor texture
	int *ceiling; // ceiling texture
	unsigned long hex_floor; // color of the floor
	unsigned long hex_ceiling; // color of the ceiling
	int size; // size of the texture
	int index; // index of the texture
	double step; // step of the texture
	double pos; // position of the texture
	int x; // x position of the texture
	int y; // y position of the texture
}	t_texture;

typedef struct s_raycast
{
	double camera_x; // x position of the camera
	double dir_x; // x direction of the camera
	double dir_y; // y direction of the camera
	int map_x; // x position of the map
	int map_y; // y position of the map
	int step_x; // x step of the ray
	int step_y; // y step of the ray
	double side_dist_x; // x distance of the side
	double side_dist_y; // y distance of the side
	double delta_dist_x; // x distance of the delta
	double delta_dist_y; // y distance of the delta
	double wall_dis; // distance of the wall
	double wall_x; // x position of the wall
	int side; // side of the wall
	int line_height; // height of the line
	int draw_start; // start of the drawing
	int draw_end; // end of the drawing
}	t_raycast;

typedef struct s_player
{
	char dir; // direction of the player
	double pos_x; // x position of the player
	double pos_y; // y position of the player
	double dir_x; // x direction of the player
	double dir_y; // y direction of the player
	double plane_x; // x plane of the player
	double plane_y; // y plane of the player
	int moved;
	int move_x;
	int move_y;
	int rotate;
}	t_player;

typedef struct s_data
{
	void *mlx;
	void *win;
	int win_height;
	int win_width;
	char **map;
	int **texture_pixels;
	int **texture;
	t_player player;
	t_texture tex;
	t_img img;
	t_raycast raycast;
	// t_map_info map_info;
}	t_data;

int *set_rgb(char *line);
unsigned long	convert_rgb_to_hex(int *rgb_tab);

void init_image(t_data *data);

void render_images(t_data *data);
void init_ray(t_raycast *raycast);

void raycasting(t_player *player, t_data *data);


#endif
