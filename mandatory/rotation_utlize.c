/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utlize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:01:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/04 12:14:01 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	get_center(t_coords coord, t_center *va)
{
	if (coord.x > va->max_x)
		va->max_x = coord.x;
	if (coord.x < va->min_x)
		va->min_x = coord.x;
	if (coord.y > va->max_y)
		va->max_y = coord.y;
	if (coord.y < va->min_y)
		va->min_y = coord.y;
	if (coord.z > va->max_z)
		va->max_z = coord.z;
	va->width = va->max_x - va->min_x;
	va->height = va->max_y - va->min_y;
}

void	initialize_centre(t_center *va)
{
	va->max_x = FLT_MIN;
	va->min_x = FLT_MAX;
	va->max_y = FLT_MIN;
	va->min_y = FLT_MAX;
	va->max_z = FLT_MIN;
}

void	aplly_isometric(t_coords **coord, t_mlx *mlx)
{
	int			i;
	int			j;
	t_center	va;

	i = 0;
	initialize_centre(&va);
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			rotation_on_z(&coord[i][j], mlx);
			rotation_on_x(&coord[i][j], mlx);
			get_center(coord[i][j], &va);
			j++;
		}
		i++;
	}
	if (mlx->inf.zoom == 1)
	{
		mlx->inf.zoom = fmin(mlx->inf.width_win / va.width, mlx->inf.height_win
				/ va.height) * 0.6;
		if (mlx->inf.zoom < 1)
			mlx->inf.zoom = 1;
	}
}
