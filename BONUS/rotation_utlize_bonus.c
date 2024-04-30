/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utlize_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:01:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/30 12:45:26 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	apply_rotation(t_coords **coord, t_mlx *mlx)
{
	int		i;
	int		j;
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			/*rotation on x*/
			tmp_y = coord[i][j].y;
			tmp_z = coord[i][j].z;
			coord[i][j].y = tmp_y * cos(mlx->rotate.angle_x) - tmp_z
				* sin(mlx->rotate.angle_x);
			coord[i][j].z = tmp_y * sin(mlx->rotate.angle_x) + tmp_z
				* cos(mlx->rotate.angle_x);
			/*rotation on y*/
			tmp_x = coord[i][j].x;
			tmp_z = coord[i][j].z;
			coord[i][j].x = tmp_x * cos(mlx->rotate.angle_y) + tmp_z
				* sin(mlx->rotate.angle_y);
			coord[i][j].z = -tmp_x * sin(mlx->rotate.angle_y) + tmp_z
				* cos(mlx->rotate.angle_y);
			/*rotation on z*/
			tmp_x = coord[i][j].x;
			tmp_y = coord[i][j].y;
			coord[i][j].x = tmp_x * cos(mlx->rotate.angle_z) - tmp_y
				* sin(mlx->rotate.angle_z);
			coord[i][j].y = tmp_y * cos(mlx->rotate.angle_z) + tmp_x
				* sin(mlx->rotate.angle_z);
			j++;
		}
		i++;
	}
}

void	rotation_on_x(t_coords **coord, t_mlx *mlx)
{
	float	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			tmp = coord[i][j].z;
			coord[i][j].z = tmp * sin(mlx->rotate.angle_x) + coord[i][j].y
				* cos(mlx->rotate.angle_x);
			coord[i][j].y = coord[i][j].y * cos(mlx->rotate.angle_x) - tmp
				* sin(mlx->rotate.angle_x);
			j++;
		}
		i++;
	}
}

void	rotation_on_y(t_coords **coord, t_mlx *mlx)
{
	float	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			tmp = coord[i][j].z;
			coord[i][j].z = tmp * cos(mlx->rotate.angle_y) - coord[i][j].x
				* sin(mlx->rotate.angle_y);
			coord[i][j].x = coord[i][j].x * cos(mlx->rotate.angle_y) + tmp
				* sin(mlx->rotate.angle_y);
			j++;
		}
		i++;
	}
}

void	rotation_on_z(t_coords **coord, t_mlx *mlx)
{
	float	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			tmp = coord[i][j].x;
			coord[i][j].x = tmp * cos(mlx->rotate.angle_z) - coord[i][j].y
				* sin(mlx->rotate.angle_z);
			coord[i][j].y = coord[i][j].y * cos(mlx->rotate.angle_z) + tmp
				* sin(mlx->rotate.angle_z);
			j++;
		}
		i++;
	}
}

void	rotation(t_coords **coord, t_mlx *mlx)
{
	rotation_on_x(coord, mlx);
	rotation_on_y(coord, mlx);
	rotation_on_z(coord, mlx);
}
