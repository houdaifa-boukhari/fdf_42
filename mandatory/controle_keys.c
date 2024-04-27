/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/27 14:40:17 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void initialize_moves(t_mlx *mlx)
{
	mlx->moves.x = 0;
	mlx->moves.y = 0;
	mlx->moves.z = 0;
	mlx->moves.zoom = 0;
	mlx->rotate.angle_x = atan(1 / sqrt(2.0));
	mlx->rotate.angle_y = 0;
	mlx->rotate.angle_z = -45.0 * (PI / 180.0);
	initialize_rotaion(mlx);
}

void initialize_rotaion(t_mlx *mlx)
{
	mlx->rotate.x = false;
	mlx->rotate.y = false;
	mlx->rotate.z = false;
}

void initialize_centre(t_da *va)
{
	va->x_min = FLT_MAX;
	va->y_min = FLT_MAX;
	va->x_max = FLT_MIN;
	va->y_max = FLT_MIN;
	va->c_x = 0;
	va->c_y = 0;
}

void manage_moves(t_mlx **mlx, int key)
{
	if (key == UP)
		(*mlx)->moves.y -= 15;
	else if (key == DOWN)
		(*mlx)->moves.y += 15;
	else if (key == RIGHT)
		(*mlx)->moves.x += 15;
	else if (key == LEFT)
		(*mlx)->moves.x -= 15;
	else if (key == ZOOM)
		(*mlx)->moves.zoom += 1;
	else if (key == MINIMIZE && ((*mlx)->moves.zoom * -1) < (*mlx)->inf.zoom - 1)
		(*mlx)->moves.zoom -= 1;
	else if (key == ROTATE_X || key == ROTATE_Y || key == ROTATE_Z)
	{
		if (key == ROTATE_X)
		{
			(*mlx)->rotate.x = true;
			(*mlx)->rotate.angle_x += 0.174532925;
		}
		else if (key == ROTATE_Y)
		{
			(*mlx)->rotate.y = true;
			(*mlx)->rotate.angle_y += 0.174532925;
		}
		else if (key == ROTATE_Z)
		{
			(*mlx)->rotate.z = true;
			(*mlx)->rotate.angle_z += 0.174532925;
		}
	}
	else if (key == R_ROTATE_X || key == R_ROTATE_Y || key == R_ROTATE_Z)
	{
		if (key == R_ROTATE_X)
		{
			(*mlx)->rotate.x = true;
			(*mlx)->rotate.angle_x -= 0.174532925;
		}
		else if (key == R_ROTATE_Y)
		{
			(*mlx)->rotate.y = true;
			(*mlx)->rotate.angle_y -= 0.174532925;
		}
		else if (key == R_ROTATE_Z)
		{
			(*mlx)->rotate.z = true;
			(*mlx)->rotate.angle_z -= 0.174532925;
		}
	}
}

int close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int manage_keys(int key_press, t_mlx *mlx)
{
	if (key_press == SHUT_DOWN)
		close_window(mlx);
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	if (key_press == UP)
		manage_moves(&mlx, UP);
	else if (key_press == DOWN)
		manage_moves(&mlx, DOWN);
	else if (key_press == RIGHT)
		manage_moves(&mlx, RIGHT);
	else if (key_press == LEFT)
		manage_moves(&mlx, LEFT);
	else if (key_press == ZOOM)
		manage_moves(&mlx, ZOOM);
	else if (key_press == MINIMIZE)
		manage_moves(&mlx, MINIMIZE);
	else if (key_press == ROTATE_X)
		manage_moves(&mlx, ROTATE_X);
	else if (key_press == ROTATE_Y)
		manage_moves(&mlx, ROTATE_Y);
	else if (key_press == ROTATE_Z)
		manage_moves(&mlx, ROTATE_Z);
	else if (key_press == R_ROTATE_X)
		manage_moves(&mlx, R_ROTATE_X);
	else if (key_press == R_ROTATE_Y)
		manage_moves(&mlx, R_ROTATE_Y);
	else if (key_press == R_ROTATE_Z)
		manage_moves(&mlx, R_ROTATE_Z);
	draw_map(mlx->coords, mlx, mlx->inf);
	initialize_rotaion(mlx);
	printf("keys is %d\n", key_press);
	return (0);
}

void get_centr(t_line *line, t_da *va)
{
	va->x_min = fmin(va->x_min, fmin(line->start_x, line->end_x));
	va->y_min = fmin(va->y_min, fmin(line->start_y, line->end_y));
	va->x_max = fmax(va->x_max, fmax(line->start_x, line->end_x));
	va->y_max = fmax(va->y_max, fmax(line->start_y, line->end_y));
	va->c_x = (va->x_max - va->x_min) / 2.0;
	va->c_y = (va->y_max - va->y_min) / 2.0;
}