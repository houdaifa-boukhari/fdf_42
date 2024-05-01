/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:11:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/01 11:31:16 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		j = -1;
		while (++j < info.width_map)
		{
			if (j < info.width_map - 1)
			{
				assign_values(coords[i][j], coords[i][j + 1], &line);
				offset_to_center(&line, mlx);
				draw_line(mlx, line);
			}
			if (i < info.height_map - 1)
			{
				assign_values(coords[i][j], coords[i + 1][j], &line);
				offset_to_center(&line, mlx);
				draw_line(mlx, line);
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
}

void	draw_line(t_mlx *mlx, t_line coords)
{
	t_data	var;
	int		j;
	int		new_color;

	j = -1;
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
	while (++j < var.steps)
	{
		var.inc_x += var.var_x;
		var.inc_y += var.var_y;
		new_color = create_gradient(coords.start_color, coords.end_color,
				(float)j / var.steps);
		my_mlx_pixel_put(&mlx, round(var.inc_x), round(var.inc_y), new_color);
	}
}
