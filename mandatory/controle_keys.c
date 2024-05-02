/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:20 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int	manage_keys(int key_press, t_mlx *mlx)
{
	if (key_press == SHUT_DOWN)
		close_window(mlx);
	return (0);
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