/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:41:40 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 17:40:09 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(char c, va_list args)
{
	void	*ptr;

	if (c == '%')
		return (putchar_('%'));
	else if (c == 'c')
		return (putchar_(va_arg(args, int)));
	else if (c == 's')
		return (putstr_(va_arg(args, char *)));
	else if (c == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr)
			return (putstr_("0x") + puthexa_((unsigned long)ptr, 'x'));
		return (putstr_("0x0"));
	}
	else if (c == 'd' || c == 'i')
		return (putnbr_(va_arg(args, int)));
	else if (c == 'u')
		return (putnbr_(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (puthexa_(va_arg(args, unsigned int), 'x'));
	else if (c == 'X')
		return (puthexa_(va_arg(args, unsigned int), 'X'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, format);
	if ((write(STDOUT_FILENO, "", 0) == -1))
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1]
			&& strchr_("cspdiuxX%", format[i + 1]))
		{
			len += check_format(format[i + 1], args);
			i++;
		}
		else if (format[i] != '%')
			len += putchar_(format[i]);
		else if (format[i] == '%')
			return (len);
		i++;
	}
	va_end(args);
	return (len);
}
