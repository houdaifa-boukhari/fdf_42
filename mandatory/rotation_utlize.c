/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utlize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:01:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/29 11:16:54 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	aplly_isometric(t_coords **coord, t_mlx *mlx)
{
	float	tmp_x;
	int		i;
	int		j;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			tmp_x = coord[i][j].x;
			coord[i][j].x = tmp_x * cos(mlx->rotate.angle_z) - coord[i][j].y
				* sin(mlx->rotate.angle_z);
			coord[i][j].y = coord[i][j].y * cos(mlx->rotate.angle_z) + tmp_x
				* sin(mlx->rotate.angle_z);
			tmp_x = coord[i][j].x;
			coord[i][j].x = tmp_x;
			coord[i][j].y = coord[i][j].y * cos(mlx->rotate.angle_x)
				- coord[i][j].z * sin(mlx->rotate.angle_x);
			coord[i][j].z = coord[i][j].y * sin(mlx->rotate.angle_x)
				+ coord[i][j].z * cos(mlx->rotate.angle_x);
			j++;
		}
		i++;
	}
}

void	rotation_on_x(t_line *line, float angle)
{
	float	tmp;

	tmp = line->start_z;
	line->start_z = tmp * sin(angle) + line->start_y * cos(angle);
	line->start_y = line->start_y * cos(angle) - tmp * sin(angle);
	tmp = line->end_z;
	line->end_z = tmp * sin(angle) + line->end_y * cos(angle);
	line->end_y = line->end_y * cos(angle) - tmp * sin(angle);
}

void	rotation_on_y(t_line *line, float angle)
{
	float	tmp;

	tmp = line->start_z;
	line->start_z = tmp * cos(angle) - line->start_x * sin(angle);
	line->start_x = line->start_x * cos(angle) + tmp * sin(angle);
	tmp = line->end_z;
	line->end_z = tmp * cos(angle) - line->end_x * sin(angle);
	line->end_x = line->end_x * cos(angle) + tmp * sin(angle);
}

void	rotation_on_z(t_line *line, float angle)
{
	float	tmp;

	tmp = line->start_x;
	line->start_x = tmp * cos(angle) - line->start_y * sin(angle);
	line->start_y = line->start_y * cos(angle) + tmp * sin(angle);
	tmp = line->end_x;
	line->end_x = tmp * cos(angle) - line->end_y * sin(angle);
	line->end_y = line->end_y * cos(angle) + tmp * sin(angle);
}

void	rotation(t_line *line, t_mlx *mlx)
{
	if (mlx->rotate.x == true)
		rotation_on_x(line, mlx->rotate.angle_x);
	else if (mlx->rotate.y == true)
		rotation_on_y(line, mlx->rotate.angle_y);
	else if (mlx->rotate.z == true)
		rotation_on_z(line, mlx->rotate.angle_z);
}
