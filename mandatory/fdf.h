#ifndef FDF_H
#define FDF_H

#include <math.h>
#include <stdio.h>
// #include "../minilibx_macos/mlx.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <limits.h>
#include "../libft/libft.h"
#include "../printf/ft_printf.h"
#include "../get_next_line/get_next_line.h"

#define PI 3.14159265


typedef struct s_map
{
	char			**map;
	struct s_map    *next;
}					t_map;

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
	float color;
}	t_coords;

typedef	struct	s_line
{
	float	start_x;
	float	start_y;
	float	start_z;
	int		start_color;
	float	end_x;
	float	end_y;
	float	end_z;
	int		end_color;
}			t_line;

typedef struct	s_data
{
    float	var_x;
	float	var_y;
	float	inc_x;
	float	inc_y;
	float	steps;
}			t_data;

typedef	struct	s_info_map
{
	float	height_win;
	float	width_win;
	float	height_map;
	float	width_map;
	float	zoom;
}		t_info_map;

typedef struct s_colors
{
	int r;
	int	g;
	int	b;
}		t_colors;

typedef struct s_moves
{
	float	x;
	float	y;
	float	z;
	float zoom;
}		t_moves;

typedef	struct s_rotation
{
	bool	x;
	bool	y;
	bool	z;
	float	angle;
}			t_rt;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_coords	**coords;
	t_info_map	inf;
	t_moves		moves;
	t_rt		rotate;
}				t_mlx;

typedef	struct s_da
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;		
}			t_da;



bool	creat_list(char *cmd, t_map **head);
void 	print_list(t_map *h);
int		count_arrays(char **str);
void	*free_list(t_map **head);
t_coords	**get_coordinates(t_map *map, t_info_map info_map);
void	draw_line(void *mlx, void *mlx_win, t_line coords);
void    aplly_isometric(t_line *line, t_mlx *mlx);
void	assign_map(t_info_map *map_info, t_map *map);
int create_gradient(int color1, int color2, double t);
// void	free_coords(t_coords **coords, t_info_map info);
int		manage_keys(int key_press, t_mlx *mlx);
int		close_window(t_mlx *mlx);
void	initialize_moves(t_mlx *mlx);
void    draw_map(t_coords **coords, t_mlx *mlx, t_info_map info);
void	assign_values(t_coords coord1, t_coords coord2, t_line *line, t_mlx *mlx);
void    offset_to_center(t_line *line, t_mlx *mlx);
void	manage_moves(t_mlx **mlx, char c);
void	rotation(t_line *line, t_mlx *mlx);
void	initialize_rotaion(t_mlx *mlx);
#endif