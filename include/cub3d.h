/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:10 by welow             #+#    #+#             */
/*   Updated: 2024/11/21 17:05:50 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define MOVE_SPEED 5
# define ROTATE_SPEED 0.1

# define SCREEN_W 1280
# define SCREEN_H 720
# define TEXTURE_SIZE 64

# define MAP_PIXEL 128
# define MAP_VIEW 4
# define MAP_PLAYER_COLOR 0x00FF00
# define MAP_WALL_COLOR 0xFF0000

typedef struct s_data
{
	void	*mlx;
	void	*win;
}			t_data;

#endif
