/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:29 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/24 21:49:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int create_gradient(int color1, int color2, double position)
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
    return (new_color.r << 16) | (new_color.g << 8) | new_color.b;
}

void	assign_map(t_info_map *map_info, t_map *map)
{
	map_info->height_map = ft_lstsize((t_list *)map);
	map_info->width_map = count_arrays(map->map);
	map_info->height_win = 1000;
	map_info->width_win = 1000;
	map_info->zoom = 25;
}

void    offset_to_center(t_line *line, t_mlx *mlx)
{
	float nb;

	nb = 2;
	line->start_x = (line->start_x + (mlx->inf.width_win / nb) - (mlx->inf.width_map * (mlx->inf.zoom + mlx->moves.zoom)) / nb) + (cos(0.523599) * (mlx->inf.zoom + mlx->moves.zoom));
	line->start_y = (line->start_y + (mlx->inf.height_win / nb) - (mlx->inf.height_map * (mlx->inf.zoom + mlx->moves.zoom)) / nb) + (sin(0.523599) * (mlx->inf.zoom + mlx->moves.zoom));
	line->end_x = (line->end_x + (mlx->inf.width_win / nb) - (mlx->inf.width_map * (mlx->inf.zoom + mlx->moves.zoom)) / nb) + (cos(0.523599) * (mlx->inf.zoom + mlx->moves.zoom));
	line->end_y = (line->end_y + (mlx->inf.height_win / nb) - (mlx->inf.height_map * (mlx->inf.zoom + mlx->moves.zoom)) / nb) + (sin(0.523599) * (mlx->inf.zoom + mlx->moves.zoom));
}

void    aplly_isometric(t_line *line, t_mlx *mlx)
{
	float	tmp;
	float	nb;

	nb = 2;
	line->start_x -= (mlx->inf.height_win / nb);
	line->start_y -= mlx->inf.width_win / nb;
	line->end_x -= mlx->inf.height_win / nb;
	line->end_y -= mlx->inf.width_win / nb;
	
	tmp = line->start_x;
	line->start_x = (line->start_x + line->start_y) * cos(0.523599);
	line->start_y = (line->start_y - tmp) * sin(0.523599) - line->start_z;
	tmp = line->end_x;
	line->end_x = (line->end_x + line->end_y) * cos(0.523599);
	line->end_y = (line->end_y - tmp) * sin(0.523599) - line->end_z;
	
	line->start_x += mlx->inf.height_win / nb;
	line->start_y += mlx->inf.width_win / nb;
	line->end_x += mlx->inf.height_win / nb;
	line->end_y += mlx->inf.width_win / nb;
}


void	rotation_on_x(t_line *line, t_mlx *mlx, float angle)
{
	float	tmp;

	line->start_z -= (mlx->inf.height_win / 2.0);
	line->start_y -= mlx->inf.width_win / 2.0;
	line->end_z -= mlx->inf.height_win / 2.0;
	line->end_y -= mlx->inf.width_win / 2.0;

	tmp = line->start_z;
	line->start_z = tmp * sin(angle) + line->start_y * cos(angle);
	line->start_y =	line->start_y * cos(angle) - tmp * sin(angle);
	tmp = line->end_z;
	line->end_z = tmp * sin(angle) + line->end_y * cos(angle);
	line->end_y = line->end_y * cos(angle) - tmp * sin(angle);

	line->start_z += mlx->inf.height_win / 2.0;
	line->start_y += mlx->inf.width_win / 2.0;
	line->end_z += mlx->inf.height_win / 2.0;
	line->end_y += mlx->inf.width_win / 2.0;
}

void	rotation_on_y(t_line *line, t_mlx *mlx, float angle)
{
	float	tmp;

	line->start_z -= (mlx->inf.height_win / 2.0);
	line->start_y -= mlx->inf.width_win / 2.0;
	line->end_z -= mlx->inf.height_win / 2.0;
	line->end_y -= mlx->inf.width_win / 2.0;

	tmp = line->start_z;
	line->start_z = tmp * cos(angle) - line->start_x * sin(angle);
	line->start_x =	line->start_x * cos(angle) + tmp * sin(angle);
	tmp = line->end_z;
	line->end_z = tmp * cos(angle) - line->end_x * sin(angle);
	line->end_x = line->end_x * cos(angle) + tmp * sin(angle);

	line->start_z += mlx->inf.height_win / 2.0;
	line->start_y += mlx->inf.width_win / 2.0;
	line->end_z += mlx->inf.height_win / 2.0;
	line->end_y += mlx->inf.width_win / 2.0;
}

void	rotation_on_z(t_line *line, t_mlx *mlx, float angle)
{
	float	tmp;

	line->start_x -= (mlx->inf.height_win / 2.0);
	line->start_y -= mlx->inf.width_win / 2.0;
	line->end_x -= mlx->inf.height_win / 2.0;
	line->end_y -= mlx->inf.width_win / 2.0;

	tmp = line->start_x;
	line->start_x = tmp * cos(angle) - line->start_y * sin(angle);
	line->start_y =	line->start_y * cos(angle) + tmp * sin(angle);
	tmp = line->end_x;
	line->end_x = tmp * cos(angle) - line->end_y * sin(angle);
	line->end_y = line->end_y * cos(angle) + tmp * sin(angle);

	// line->start_x += mlx->inf.height_win / 2.0;
	// line->start_y += mlx->inf.width_win / 2.0;
	// line->end_x += mlx->inf.height_win / 2.0;
	// line->end_y += mlx->inf.width_win / 2.0;
}

void	rotation(t_line *line, t_mlx *mlx)
{
	float	new_angle;

	new_angle = (mlx->rotate.angle) * (PI / 180.0);
	if (mlx->rotate.x == true)
		rotation_on_x(line, mlx, new_angle);
	else if (mlx->rotate.y == true)
		rotation_on_y(line, mlx, new_angle);
	else if (mlx->rotate.z == true)
		rotation_on_z(line, mlx, new_angle);
}