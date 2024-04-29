/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:14 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	manage_moves(t_mlx **mlx, int key)
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
	else if (key == MINIMIZE && ((*mlx)->moves.zoom * -1) < (*mlx)->inf.zoom
		- 1)
		(*mlx)->moves.zoom -= 1;
	draw_map((*mlx)->coords, *mlx, (*mlx)->inf);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int	manage_keys(int key_press, t_mlx *mlx)
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
	else
		handle_keys_rotation(&mlx, key_press);
	return (0);
}

void	handle_rotate_x(t_mlx **mlx, int key)
{
	(*mlx)->rotate.x = true;
	if (key == ROTATE_X)
		(*mlx)->rotate.angle_x += 5 * (PI / 180);
	else if (key == R_ROTATE_X)
		(*mlx)->rotate.angle_x -= 5 * (PI / 180);
}

void	handle_keys_rotation(t_mlx **mlx, int key)
{
	if (key == ROTATE_X || key == R_ROTATE_X)
		handle_rotate_x(mlx, key);
	else if (key == ROTATE_Z)
	{
		(*mlx)->rotate.z = true;
		(*mlx)->rotate.angle_z += 5 * (PI / 180);
	}
	else if (key == R_ROTATE_Z)
	{
		(*mlx)->rotate.z = true;
		(*mlx)->rotate.angle_z -= 5 * (PI / 180);
	}
	if (key == ROTATE_Y)
	{
		(*mlx)->rotate.y = true;
		(*mlx)->rotate.angle_y += 5 * (PI / 180);
	}
	else if (key == R_ROTATE_Y)
	{
		(*mlx)->rotate.y = true;
		(*mlx)->rotate.angle_y -= 5 * (PI / 180);
	}
	draw_map((*mlx)->coords, *mlx, (*mlx)->inf);
	initialize_rotaion(*mlx);
}
