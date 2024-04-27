/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:29 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/27 14:48:08 by hel-bouk         ###   ########.fr       */
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
	line->start_x += mlx->inf.width_win / 2.0;
	line->start_y += mlx->inf.height_win / 2.0;
	line->end_x += mlx->inf.width_win / 2.0;
	line->end_y += mlx->inf.height_win / 2.0;
}