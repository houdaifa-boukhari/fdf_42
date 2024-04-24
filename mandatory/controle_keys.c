/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/24 21:46:38 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void initialize_moves(t_mlx *mlx)
{
	mlx->moves.x = 0;
	mlx->moves.y = 0;
	mlx->moves.z = 0;
	mlx->moves.zoom =  0;
	mlx->rotate.angle = 0;
	initialize_rotaion(mlx);
}

void	initialize_rotaion(t_mlx *mlx)
{
	mlx->rotate.x = false;
	mlx->rotate.y = false;
	mlx->rotate.z = false;
}

void	manage_moves(t_mlx **mlx, char c)
{
	if (c == 'u')
		(*mlx)->moves.y -= 15;
	else if (c == 'd')
		(*mlx)->moves.y += 15;
	else if (c == 'r')
		(*mlx)->moves.x += 15;
	else if (c == 'l')
		(*mlx)->moves.x -= 15;
	else if (c == 'z')
		(*mlx)->moves.zoom += 1;
	else if (c == 'm' && ((*mlx)->moves.zoom * -1) < (*mlx)->inf.zoom -1)
		(*mlx)->moves.zoom -= 1;
	else if (c == 'x' || c == 'y' || c == 'n')
	{
		if (c == 'x')
			(*mlx)->rotate.x = true;
		else if (c == 'y')
			(*mlx)->rotate.y = true;
		else if (c == 'n')
			(*mlx)->rotate.z = true;
		(*mlx)->rotate.angle += 5;
		(*mlx)->rotate.angle = fmod((*mlx)->rotate.angle, 360.0);
		if ((*mlx)->rotate.angle < 0)
			(*mlx)->rotate.angle += 360.0;
	}
	else if (c == 'i' || c == 'o' || c == 'p')
	{
		if (c == 'i')
			(*mlx)->rotate.x = true;
		else if (c == 'o')
			(*mlx)->rotate.y = true;
		else if (c == 'p')
			(*mlx)->rotate.z = true;
		(*mlx)->rotate.angle -= 5;
		(*mlx)->rotate.angle = fmod((*mlx)->rotate.angle, 360.0);
		if ((*mlx)->rotate.angle < 0)
			(*mlx)->rotate.angle += 360.0;
	}
}

int close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int	manage_keys(int key_press, t_mlx *mlx)
{
	if (key_press == 53)
		close_window(mlx);
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	if (key_press == 13)
		manage_moves(&mlx, 'u');
	else if (key_press == 1)
		manage_moves(&mlx, 'd');
	else if (key_press == 2)
		manage_moves(&mlx, 'r');
	else if (key_press == 0)
		manage_moves(&mlx, 'l');
	else if (key_press == 69)
		manage_moves(&mlx, 'z');
	else if (key_press == 78)
		manage_moves(&mlx, 'm');
	else if (key_press == 83)
		manage_moves(&mlx, 'x');
	else if (key_press == 85)
		manage_moves(&mlx, 'y');
	else if (key_press == 87)
		manage_moves(&mlx, 'n');
	else if (key_press == 84)
		manage_moves(&mlx, 'i');
	else if (key_press == 86)
		manage_moves(&mlx, 'o');
	else if (key_press == 88)
		manage_moves(&mlx, 'p');
	draw_map(mlx->coords, mlx, mlx->inf);
	initialize_rotaion(mlx);
	printf("keys is %d\n", key_press);
	return (0);
}

void	get_centr(t_line line)
{
	static t_da va;

	va.x_min = fmin(va.x_min, fmin(line.start_x, line.end_x));
    va.y_min = fmin(va.y_min, fmin(line.start_y, line.end_y));
    va.x_max = fmax(va.x_max, fmax(line.start_x, line.end_x));
    va.y_max = fmax(va.y_max, fmax(line.start_y, line.end_y));
}