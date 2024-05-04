/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:10:21 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/04 09:15:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	random_color(void)
{
	t_colors	color;

	srand(time(NULL));
	color.r = rand() % 256;
	color.g = rand() % 256;
	color.b = rand() % 256;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	show_instructions(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 10, 0xFF0000, "ESC: Exit");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 50, 0xFF0000, "WASD: translate");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 70, 0xFF0000, "+/-: Zoom");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 30, 0xFF0000, "P: Paralell");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 90, 0xFF0000, 
		"Rotation on x: 1, 2");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 110, 0xFF0000, 
		"Rotation on y: 3, 4");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 130, 0xFF0000, 
		"Rotation on z: 5, 6");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 150, 0xFF0000,
		"B: enable/disable bonus");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 170, 0xFF0000,
		"c: enable/disable random color");
}

void	draw_bonus(t_coords **coords, t_mlx *mlx, t_info info)
{
	t_line	line;
	int		i;
	int		j;

	i = -1;
	while (++i < info.height_map)
	{
		j = -1;
		while (++j < info.width_map)
		{
			if (i < info.height_map - 1 && j < info.width_map - 1)
				assign_values(coords[i][j], coords[i + 1][j + 1], &line, mlx);
			offset_to_center(&line, mlx);
			draw_line(mlx, line);
			if (i < info.height_map - 1 && j < info.width_map - 1)
				assign_values(coords[i + 1][j], coords[i][j + 1], &line, mlx);
			offset_to_center(&line, mlx);
			draw_line(mlx, line);
		}
	}
}
