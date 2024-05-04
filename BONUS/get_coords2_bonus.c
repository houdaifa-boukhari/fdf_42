/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:30:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/04 10:31:38 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	va->width = va->max_x - va->min_x;
	va->height = va->max_y - va->min_y;
}

int	get_color(char *str)
{
	int		color;
	char	*new;

	new = ft_strchr(str, ',');
	if (new)
		color = hexa_to_int(new + 3);
	else
		return (0xFFFFFF);
	return (color);
}

void	initialize_centre(t_center *va)
{
	va->max_x = FLT_MIN;
	va->min_x = FLT_MAX;
	va->max_y = FLT_MIN;
	va->min_y = FLT_MAX;
}

void	aplly_scale(t_coords **coord, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx->inf.height_map)
	{
		j = 0;
		while (j < mlx->inf.width_map)
		{
			coord[i][j].x *= mlx->inf.zoom;
			coord[i][j].y *= mlx->inf.zoom;
			coord[i][j].z *= mlx->inf.zoom;
			j++;
		}
		i++;
	}
}

void	assign_values(t_coords coord1, t_coords coord2, t_line *line,
		t_mlx *mlx)
{
	line->start_x = (coord1.x / mlx->inf.zoom) * (mlx->inf.zoom
			+ mlx->moves.zoom) + mlx->moves.x;
	line->start_y = ((coord1.y / mlx->inf.zoom) * (mlx->inf.zoom
				+ mlx->moves.zoom) + mlx->moves.y) * 0.75;
	line->start_z = (coord1.z / mlx->inf.zoom) * (mlx->inf.zoom
			+ mlx->moves.zoom) + mlx->moves.z;
	line->end_x = (coord2.x / mlx->inf.zoom) * (mlx->inf.zoom + mlx->moves.zoom)
		+ mlx->moves.x;
	line->end_y = ((coord2.y / mlx->inf.zoom) * (mlx->inf.zoom
				+ mlx->moves.zoom) + mlx->moves.y) * 0.75;
	line->end_z = (coord2.z / mlx->inf.zoom) * (mlx->inf.zoom + mlx->moves.zoom)
		+ mlx->moves.z;
	if (mlx->moves.color == true)
	{
		line->start_color = random_color();
		line->end_color = random_color();
	}
	else
	{
		line->start_color = coord1.color;
		line->end_color = coord2.color;
	}
}
