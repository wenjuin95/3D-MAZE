/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:10 by welow             #+#    #+#             */
/*   Updated: 2024/11/26 13:19:14 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <X11/X.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

////laptop
//# define MOVE_SPEED 0.011
//# define ROTATE_SPEED 0.03

//campus
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

////laptop
//# define SCREEN_W 1280
//# define SCREEN_H 1024

//campus
# define SCREEN_W 640
# define SCREEN_H 480
# define TEXTURE_SIZE 64

# define MAP_PIXEL 128
# define MAP_VIEW 4

enum	e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
};

typedef struct s_img
{
	void	*img;
	int		*img_addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_tex
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		*floor;
	int		*ceiling;
	size_t	hex_floor;
	size_t	hex_ceiling;
	int		tex_size;
	int		tex_index;
	double	step;
	double	position;
	int		tex_x;
	int		tex_y;
}	t_tex;

typedef struct s_raycast
{
	double	camera;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dis;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_raycast;

typedef struct s_map_info
{
	char	**map;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
	t_img	*img;
}	t_map_info;

typedef struct s_player
{
	char	*dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		moved;
	int		moved_x;
	int		moved_y;
	int		rotated;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	char		**map;
	int			**tex_pixel;
	int			**tex;
	t_player	player;
	t_raycast	ray;
	t_img		img;
	t_tex		texture;
	t_map_info	map_info;
}	t_data;

#endif
