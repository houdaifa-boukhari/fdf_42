/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:43 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/05 12:34:18 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

bool	check_map(t_map *current)
{
	int	size;

	if (!current)
		ft_error("map is empty\n");
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

	str = ft_strrchr(file, '.');
	if (str == NULL || ft_strncmp(str, ".fdf", 4))
		ft_error("Invalid file extension\n");
	fd = open(file, O_RDONLY);
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

void	assign_mlx(t_mlx *mlx, t_map *map)
{
	mlx->coords = get_coordinates(map, mlx->inf);
	mlx->cpy_coords = get_coordinates(map, mlx->inf);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->inf.height_win,
			mlx->inf.width_win, "fdf");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->inf.height_img,
			mlx->inf.width_img);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	initialize_moves(mlx);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	mlx;
	t_mlx	*p_mlx;

	map = NULL;
	p_mlx = &mlx;
	if (argc == 2)
	{
		if (handle_input(argv[1], &map) == false)
			ft_error("Error\n");
		assign_map(&mlx.inf, map);
		assign_mlx(&mlx, map);
		initialize_moves(&mlx);
		apply_rotation(mlx.coords, &mlx);
		aplly_scale(mlx.coords, &mlx);
		aplly_scale(mlx.cpy_coords, &mlx);
		draw_map(mlx.coords, &mlx, mlx.inf);
		show_instructions(&mlx);
		mlx_hook(mlx.mlx_win, 17, 0, close_window, &p_mlx);
		mlx_key_hook(mlx.mlx_win, manage_keys, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
		ft_putstr_fd("Usage: ./fdf_bonus map.fdf\n", 2);
}
