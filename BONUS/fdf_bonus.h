/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:38:14 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/30 12:17:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# define PI 3.14159265
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ZOOM 69
# define MINIMIZE 78
# define ROTATE_X 83
# define ROTATE_Y 85
# define ROTATE_Z 87
# define R_ROTATE_X 84
# define R_ROTATE_Y 86
# define R_ROTATE_Z 88
# define SHUT_DOWN 53
# define PARALELL 35

typedef struct s_map
{
	char			**map;
	struct s_map	*next;
}					t_map;

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
	float	color;
}			t_coords;

typedef struct s_line
{
	float	start_x;
	float	start_y;
	float	start_z;
	int		start_color;
	int		end_color;
	float	end_x;
	float	end_y;
	float	end_z;
}			t_line;

typedef struct s_data
{
	float	var_x;
	float	var_y;
	float	inc_x;
	float	inc_y;
	float	steps;
}			t_data;

typedef struct s_info
{
	float	height_win;
	float	width_win;
	float	height_map;
	float	width_map;
	float	zoom;
}			t_info;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}		t_colors;

typedef struct s_moves
{
	float	x;
	float	y;
	float	z;
	float	zoom;
}			t_moves;

typedef struct s_rotation
{
	bool	x;
	bool	y;
	bool	z;
	float	angle_x;
	float	angle_y;
	float	angle_z;
}			t_rt;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	t_coords		**coords;
	t_coords		**cpy_coords;
	t_info			inf;
	t_moves			moves;
	t_rt			rotate;
}					t_mlx;

t_coords	**get_coordinates(t_map *map, t_info info_map);
bool		creat_list(char *cmd, t_map **head);
int			count_arrays(char **str);
void		*free_list(t_map **head);
void		draw_line(void *mlx, void *mlx_win, t_line coords);
void		assign_map(t_info *map_info, t_map *map);
int			create_gradient(int color1, int color2, double t);
int			manage_keys(int key_press, t_mlx *mlx);
int			close_window(t_mlx *mlx);
void		initialize_moves(t_mlx *mlx);
void		draw_map(t_coords **coords, t_mlx *mlx, t_info info);
void		assign_values(t_coords coord1, t_coords coord2,
				t_line *line, t_mlx *mlx);
void		offset_to_center(t_line *line, t_mlx *mlx);
void		manage_moves(t_mlx **mlx, int key);
void		aplly_isometric(t_coords **coord, t_mlx *mlx);	
void		rotation_on_x(t_coords **coord, t_mlx *mlx);
void		rotation_on_y(t_coords **coord, t_mlx *mlx);
void		rotation_on_z(t_coords **coord, t_mlx *mlx);
void		rotation(t_coords **coord, t_mlx *mlx);
void		handle_keys_rotation(t_mlx **mlx, int key);
int			get_color(char *str);
void		apply_rotation(t_coords **coord, t_mlx *mlx);

#endif