/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utlize_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:01:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/04 12:16:00 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotation_on_z(t_coords *coord, t_mlx *mlx)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = coord->x;
	tmp_y = coord->y;
	coord->x = tmp_x * cos(mlx->rotate.angle_z) - tmp_y
		* sin(mlx->rotate.angle_z);
	coord->y = tmp_y * cos(mlx->rotate.angle_z) + tmp_x
		* sin(mlx->rotate.angle_z);
}

void	rotation_on_y(t_coords *coord, t_mlx *mlx)
{
	float	tmp_x;
	float	tmp_z;

	tmp_x = coord->x;
	tmp_z = coord->z;
	coord->x = tmp_x * cos(mlx->rotate.angle_y) + tmp_z
		* sin(mlx->rotate.angle_y);
	coord->z = -tmp_x * sin(mlx->rotate.angle_y) + tmp_z
		* cos(mlx->rotate.angle_y);
}

void	rotation_on_x(t_coords *coord, t_mlx *mlx)
{
	float	tmp_y;
	float	tmp_z;

	tmp_y = coord->y;
	tmp_z = coord->z;
	coord->y = tmp_y * cos(mlx->rotate.angle_x) - tmp_z
		* sin(mlx->rotate.angle_x);
	coord->z = tmp_y * sin(mlx->rotate.angle_x) + tmp_z
		* cos(mlx->rotate.angle_x);
}

void	apply_rotation(t_coords **coord, t_mlx *mlx)
{
	t_center	va;
	int			i;
	int			j;

	i = -1;
	initialize_centre(&va);
	while (++i < mlx->inf.height_map)
	{
		j = -1;
		while (++j < mlx->inf.width_map)
		{
			rotation_on_z(&coord[i][j], mlx);
			rotation_on_y(&coord[i][j], mlx);
			rotation_on_x(&coord[i][j], mlx);
			get_center(coord[i][j], &va);
		}
	}
	if (mlx->inf.zoom == 1)
	{
		mlx->inf.zoom = fmin(mlx->inf.width_win / va.width, mlx->inf.height_win
				/ va.height) * 0.6;
		if (mlx->inf.zoom < 1)
			mlx->inf.zoom = 1;
	}
}
