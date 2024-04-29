/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilize_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:11:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:09 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	count_arrays(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_coords	**allocate_coords(t_info inf)
{
	t_coords	**coords;
	int			i;

	i = 0;
	coords = (t_coords **)malloc(sizeof(t_coords *) * inf.height_map);
	if (!coords)
		return (NULL);
	while (i < inf.height_map)
	{
		coords[i] = (t_coords *)malloc(sizeof(t_coords) * inf.width_map);
		if (!coords[i])
			return (NULL);
		i++;
	}
	return (coords);
}

t_coords	**get_coordinates(t_map *map, t_info inf)
{
	t_coords	**coords;
	int			i;
	int			j;

	j = 0;
	coords = allocate_coords(inf);
	while (map)
	{
		i = 0;
		while (map->map[i])
		{
			coords[j][i].x = i * inf.zoom - ((inf.width_map * inf.zoom) / 2.0);
			coords[j][i].y = j * inf.zoom - ((inf.height_map * inf.zoom) / 2.0);
			coords[j][i].z = ft_atoi(map->map[i]) * inf.zoom;
			coords[j][i].color = get_color(map->map[i]);
			i++;
		}
		j++;
		map = map->next;
	}
	return (coords);
}

void	draw_map(t_coords **coords, t_mlx *mlx, t_info info)
{
	t_line	line;
	int		i;
	int		j;

	i = -1;
	while (++i < info.height_map)
	{
		j = 0;
		while (j < info.width_map)
		{
			if (j < info.width_map - 1)
			{
				assign_values(coords[i][j], coords[i][j + 1], &line, mlx);
				offset_to_center(&line, mlx);
				draw_line(mlx->mlx, mlx->mlx_win, line);
			}
			if (i < info.height_map - 1)
			{
				assign_values(coords[i][j], coords[i + 1][j], &line, mlx);
				offset_to_center(&line, mlx);
				draw_line(mlx->mlx, mlx->mlx_win, line);
			}
			j++;
		}
	}
}

void	draw_line(void *mlx, void *mlx_win, t_line coords)
{
	t_data	var;
	int		j;
	int		new_color;

	j = 0;
	var.var_x = coords.end_x - coords.start_x;
	var.var_y = coords.end_y - coords.start_y;
	if (fabs(var.var_x) > fabs(var.var_y))
		var.steps = fabs(var.var_x);
	else
		var.steps = fabs(var.var_y);
	var.var_x = var.var_x / var.steps;
	var.var_y = var.var_y / var.steps;
	var.inc_x = coords.start_x;
	var.inc_y = coords.start_y;
	while (j < var.steps)
	{
		var.inc_x += var.var_x;
		var.inc_y += var.var_y;
		new_color = create_gradient(coords.start_color, coords.end_color,
				(float)j / var.steps);
		mlx_pixel_put(mlx, mlx_win, round(var.inc_x), round(var.inc_y),
			new_color);
		j++;
	}
}