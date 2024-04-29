/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:43 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

bool	check_map(t_map *current)
{
	int	size;

	if (!current)
		return (false);
	size = count_arrays(current->map);
	current = current->next;
	while (current)
	{
		if (size != count_arrays(current->map))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	handle_input(char *file, t_map **map)
{
	char	*str;
	int		fd;

	str = ft_strnstr(file, ".fdf", ft_strlen(file));
	if (str == NULL || *(str + 4) != '\0')
		return (false);
	fd = open(file, O_RDWR, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	while (creat_list(get_next_line(fd), map))
		;
	if (check_map(*map) == false)
	{
		free_list(map);
		return (false);
	}
	return (true);
}

void	assign_values(t_coords coord1, t_coords coord2, t_line *line,
		t_mlx *mlx)
{
	line->start_x = (coord1.x / mlx->inf.zoom) * (mlx->inf.zoom
			+ mlx->moves.zoom) + mlx->moves.x;
	line->start_y = (coord1.y / mlx->inf.zoom) * (mlx->inf.zoom
			+ mlx->moves.zoom) + mlx->moves.y;
	line->start_z = (coord1.z / mlx->inf.zoom) * (mlx->inf.zoom
			+ mlx->moves.zoom) + mlx->moves.z;
	line->start_color = coord1.color;
	line->end_x = (coord2.x / mlx->inf.zoom) * (mlx->inf.zoom + mlx->moves.zoom)
		+ mlx->moves.x;
	line->end_y = (coord2.y / mlx->inf.zoom) * (mlx->inf.zoom + mlx->moves.zoom)
		+ mlx->moves.y;
	line->end_z = (coord2.z / mlx->inf.zoom) * (mlx->inf.zoom + mlx->moves.zoom)
		+ mlx->moves.z;
	line->end_color = coord2.color;
	if (mlx->rotate.x || mlx->rotate.y || mlx->rotate.z)
		rotation(line, mlx);
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

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	mlx;

	map = NULL;
	if (argc == 2)
	{
		if (handle_input(argv[1], &map) == false)
		{
			ft_putstr_fd("Error\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		assign_map(&mlx.inf, map);
		mlx.coords = get_coordinates(map, mlx.inf);
		free_list(&map);
		mlx.mlx = mlx_init();
		mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.inf.height_win,
				mlx.inf.width_win, "fdf");
		initialize_moves(&mlx);
		aplly_isometric(mlx.coords, &mlx);
		draw_map(mlx.coords, &mlx, mlx.inf);
		mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
		mlx_key_hook(mlx.mlx_win, manage_keys, &mlx);
		mlx_loop(mlx.mlx);
	}
}
