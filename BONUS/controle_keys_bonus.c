/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/04 09:25:38 by hel-bouk         ###   ########.fr       */
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
	else if (key == MINIMIZE && ((*mlx)->moves.zoom + (*mlx)->inf.zoom) > 1)
		(*mlx)->moves.zoom -= 1;
	else if (key == BONUS && (*mlx)->moves.bonus == true)
		(*mlx)->moves.bonus = false;
	else if (key == BONUS && (*mlx)->moves.bonus == false)
		(*mlx)->moves.bonus = true;
	else if (key == R_COLOR && (*mlx)->moves.color == true)
		(*mlx)->moves.color = false;
	else if (key == R_COLOR && (*mlx)->moves.color == false)
		(*mlx)->moves.color = true;
	draw_map((*mlx)->coords, *mlx, (*mlx)->inf);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int	manage_keys(int key, t_mlx *mlx)
{
	if (key == SHUT_DOWN)
		close_window(mlx);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->inf.width_img,
			mlx->inf.height_img);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	if (key == UP || key == DOWN || key == RIGHT)
		manage_moves(&mlx, key);
	else if (key == LEFT || key == ZOOM || key == MINIMIZE)
		manage_moves(&mlx, key);
	else if (key == BONUS || key == R_COLOR)
		manage_moves(&mlx, key);
	else if (key == PARALELL)
		draw_map(mlx->cpy_coords, mlx, mlx->inf);
	else
		handle_keys_rotation(&mlx, key);
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
