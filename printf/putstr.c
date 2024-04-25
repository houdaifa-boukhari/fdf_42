/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:31:18 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:26:54 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putstr_(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			write(STDOUT_FILENO, &str[i++], 1);
		return (i);
	}
	return (putstr_("(null)"));
}
