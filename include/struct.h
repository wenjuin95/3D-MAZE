/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:24:01 by welow             #+#    #+#             */
/*   Updated: 2024/12/26 15:14:36 by welow            ###   ########.fr       */
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
	int		maply_height;
	char	**map;
	int		map_height;
	int		*array_width;
	int		map_width;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		*floor;
	int		*ceiling;
	char	**map_layout;
	size_t	floor_hex;
	size_t	ceiling_hex;
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
	int		texture_size;
	int		texture_index;
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
