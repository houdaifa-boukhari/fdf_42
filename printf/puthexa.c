/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:36:58 by hel-bouk          #+#    #+#             */
/*   Updated: 2023/12/25 15:15:25 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	puthexa_(unsigned long nb, char format)
{
	char	*base;
	char	*base1;
	int		i;

	i = 1;
	base = "0123456789ABCDEF";
	base1 = "0123456789abcdef";
	if (nb >= 16)
	{
		i += puthexa_(nb / 16, format);
		puthexa_(nb % 16, format);
	}
	else if (format == 'X')
		putchar_(base[nb]);
	else
		putchar_(base1[nb]);
	return (i);
}
