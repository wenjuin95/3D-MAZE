/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:24:01 by welow             #+#    #+#             */
/*   Updated: 2024/12/27 10:30:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"

enum	e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
};

typedef struct s_minimap
{
	int			visible_x;
	int			visible_y;
	int			view_distance;
	int			size;
	int			texture_size;
	char		**map;
}	t_minimap;

typedef struct s_map
{
	char	**file; // result of gnl
	int		file_height; // number of rows in the file
	int		*array_width; //cause the map is not a rectangle
	int		map_width; // the largest width of the map
	int		map_start; // the index offirst row of the map
	int		map_height; // number of rows in the map
	char	**map; // 2D array of the map
	char	*north; // path to the north texture
	char	*south; // path to the south texture
	char	*west; // path to the west texture
	char	*east; // path to the east texture
	char	*sprite; //	path to the sprite texture
	int		*floor; // RGB value of the floor
	int		*ceiling; // RGB value of the ceiling
	size_t	floor_hex; // hex value of the floor
	size_t	ceiling_hex; // hex value of the ceiling
}	t_map;

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
	int		**pixel;
	int		**data;
	int		size;
	int		direction;
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

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		moved_x;
	int		moved_y;
	int		rotated;
	float	angle;
}	t_player;

#endif
