/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/02 12:37:37 by hel-bouk         ###   ########.fr       */
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
	else if (key == PARALELL)
	{
		(*mlx)->rotate.angle_x = 0;
		(*mlx)->rotate.angle_y = 0;
		(*mlx)->rotate.angle_z = 0;
		draw_map((*mlx)->cpy_coords, *mlx, (*mlx)->inf);
		return ;
	}
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
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->inf.width_img,
			mlx->inf.height_img);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
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
	else if (key_press == PARALELL)
		manage_moves(&mlx, PARALELL);
	else
		handle_keys_rotation(&mlx, key_press);
	return (0);
}

void	handle_keys_rotation(t_mlx **mlx, int key)
{
	initalize_rotation(&((*mlx)->rotate));
	if (key == ROTATE_X)
		(*mlx)->rotate.angle_x = 5 * (PI / 180);
	else if (key == R_ROTATE_X)
		(*mlx)->rotate.angle_x = -5 * (PI / 180);
	else if (key == ROTATE_Z)
		(*mlx)->rotate.angle_z = 5 * (PI / 180);
	else if (key == R_ROTATE_Z)
		(*mlx)->rotate.angle_z = -5 * (PI / 180);
	else if (key == ROTATE_Y)
		(*mlx)->rotate.angle_y = 5 * (PI / 180);
	else if (key == R_ROTATE_Y)
		(*mlx)->rotate.angle_y = -5 * (PI / 180);
	apply_rotation((*mlx)->coords, *mlx);
	draw_map((*mlx)->coords, *mlx, (*mlx)->inf);
}

void	my_mlx_pixel_put(t_mlx **mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= (*mlx)->inf.width_img
		|| y >= (*mlx)->inf.height_img)
		return ;
	dst = (*mlx)->img.addr + (y * (*mlx)->img.line_length + x * (4));
	*(unsigned int *)dst = color;
}
