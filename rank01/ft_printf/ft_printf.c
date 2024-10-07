/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:40:30 by bschwell          #+#    #+#             */
/*   Updated: 2024/05/03 10:19:35 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static int	ft_parsefmt(const char conv, va_list *ap)
{
	if (conv == 'c')
		return (ft_putchar(va_arg(*ap, int)));
	if (conv == 's')
		return (ft_putstr(va_arg(*ap, char *)));
	if (conv == 'd' || conv == 'i')
		return (ft_putnbr(va_arg(*ap, int), 0));
	if (conv == 'u')
		return (ft_putnbr(va_arg(*ap, int), 1));
	if (conv == 'x')
		return (ft_putnbr_base(va_arg(*ap, int), "0123456789abcdef"));
	if (conv == 'X')
		return (ft_putnbr_base(va_arg(*ap, int), "0123456789ABCDEF"));
	if (conv == 'p')
		return (ft_putptr(va_arg(*ap, unsigned long)));
	if (conv == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			res;
	int			i;

	res = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			res += ft_parsefmt(format[i + 1], &args);
			i++;
		}
		else
		{
			res += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (res);
}
