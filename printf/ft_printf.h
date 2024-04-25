/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:06:35 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:01:28 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		putnbr_(long nb);
int		putchar_(char c);
int		putstr_(char *str);
int		puthexa_(unsigned long nb, char format);
int		putaddress_(void *ptr);
int		ft_printf(const char *format, ...);
char	*strchr_(const char *s, int c);

#endif
