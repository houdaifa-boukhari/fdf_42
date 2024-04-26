/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:11:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/26 20:59:27 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int count_arrays(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
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

t_coords	**get_coordinates(t_map *map, t_info_map info_map)
{
	t_coords	**coords;
	int				i;
	int				j;

	i = 0;
	j = 0;
	coords = (t_coords **)malloc(sizeof(t_coords *) * info_map.height_map);
	if (!coords)
		return (NULL);
	while (i < info_map.height_map)
	{
		coords[i] = (t_coords *)malloc(sizeof(t_coords) * info_map.width_map);
		if (!coords[i])
			return (NULL);
		i++;
	}
	while (map)
	{
		i = 0;
		while (map->map[i])
		{
			coords[j][i].x = i * info_map.zoom;
			coords[j][i].y = j * info_map.zoom;
			coords[j][i].z = ft_atoi(map->map[i]) * info_map.zoom;
			coords[j][i].color = get_color(map->map[i]);
			i++;
		}
		j++;
		map = map->next;
	}
	return (coords);
}



void    draw_map(t_coords **coords, t_mlx *mlx, t_info_map info)
{
	t_line	line;
	static t_da	va;
	int		i;
	int		j;

	i = 0;
	initialize_centre(&va);
	while (i < info.height_map)
	{
		j  = 0;
		while (j < info.width_map)
		{
			if (j < info.width_map - 1)
			{
				assign_values(coords[i][j], coords[i][j + 1], &line, mlx);
				// offset_to_center(&line, mlx);
				aplly_isometric(&line, mlx);
				get_centr(&line, &va);
				draw_line(mlx->mlx, mlx->mlx_win, line);
			}
			if (i < info.height_map - 1)
			{
				assign_values(coords[i][j], coords[i + 1][j], &line, mlx);
				// offset_to_center(&line, mlx);
				aplly_isometric(&line, mlx);
				get_centr(&line, &va);
				draw_line(mlx->mlx, mlx->mlx_win,line);
			}
			j++;
		}
		i++;
	}
	// printf("max x: %f\nmin x : %f\nmax y : %f\nmin y: %f\ncentr x : %f\ncentre y: %f----------\n", va.x_max, va.x_min, va.y_max, va.y_min, va.c_x, va.c_y);
}

void	draw_line(void *mlx, void *mlx_win, t_line coords)
{
	t_data	var;
	int		j;
	int     new_color;

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
		new_color = create_gradient(coords.start_color, coords.end_color, (float)j / var.steps);
		mlx_pixel_put(mlx, mlx_win, round(var.inc_x) , round(var.inc_y), new_color);
		j++;
	}
}
