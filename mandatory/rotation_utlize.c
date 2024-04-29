/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utlize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:01:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/29 12:44:24 by hel-bouk         ###   ########.fr       */
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
