/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:29 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/01 15:13:46 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_gradient(int color1, int color2, double position)
{
	t_colors	st_color;
	t_colors	end_color;
	t_colors	new_color;

	st_color.r = (color1 >> 16) & 0xFF;
	st_color.g = (color1 >> 8) & 0xFF;
	st_color.b = color1 & 0xFF;
	end_color.r = (color2 >> 16) & 0xFF;
	end_color.g = (color2 >> 8) & 0xFF;
	end_color.b = color2 & 0xFF;
	new_color.r = st_color.r + (position * (end_color.r - st_color.r));
	new_color.g = st_color.g + (position * (end_color.g - st_color.g));
	new_color.b = st_color.b + (position * (end_color.b - st_color.b));
	return ((new_color.r << 16) | (new_color.g << 8) | new_color.b);
}

void	assign_map(t_mlx *mlx, t_map *map)
{
	mlx->inf.height_map = ft_lstsize((t_list *)map);
	mlx->inf.width_map = count_arrays(map->map);
	mlx->inf.height_win = 1000;
	mlx->inf.width_win = 1000;
	mlx->inf.height_img = 1000;
	mlx->inf.width_img = 1000;
    mlx->inf.zoom = 8;
}

void	offset_to_center(t_line *line, t_mlx *mlx)
{
	line->start_x += mlx->inf.width_win / 2.0;
	line->start_y += mlx->inf.height_win / 2.0;
	line->end_x += mlx->inf.width_win / 2.0;
	line->end_y += mlx->inf.height_win / 2.0;
}

void	initialize_moves(t_mlx *mlx)
{
	mlx->rotate.angle_x = atan(sqrt(2.0));
	mlx->rotate.angle_z = -45.0 * (PI / 180.0);
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
