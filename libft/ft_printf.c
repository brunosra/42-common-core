/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:40:30 by bschwell          #+#    #+#             */
/*   Updated: 2024/07/03 15:21:33 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_u_fd(int n, int fd)
{
	long int	i;
	size_t		count;

	i = (unsigned int) n;
	count = 0;
	if (i < 0)
	{
		count += ft_putchar_fd('-', fd);
		i *= -1;
	}
	if (i < 10)
		count += ft_putchar_fd((i % 10) + '0', fd);
	else
	{
		count += ft_putnbr_fd(i / 10, fd);
		count += ft_putnbr_fd(i % 10, fd);
	}
	return (count);
}

static int	ft_putnbr_base_ptr_fd(unsigned long ptr, char *base, int fd)
{
	size_t			count;
	size_t			base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (ptr < base_len)
		count += ft_putchar_fd(base[ptr % base_len], fd);
	else
	{
		count += ft_putnbr_base_ptr_fd(ptr / base_len, base, fd);
		count += ft_putnbr_base_ptr_fd(ptr % base_len, base, fd);
	}
	return (count);
}

static int	ft_putptr_fd(unsigned long ptr, int fd)
{
	int	count;

	count = 0;
	if (ptr == 0)
		count += ft_putstr_fd("(nil)", fd);
	else
	{
		count += ft_putstr_fd("0x", fd);
		count += ft_putnbr_base_ptr_fd(ptr, "0123456789abcdef", fd);
	}
	return (count);
}

static int	ft_parsefmt(const char conv, va_list *ap)
{
	if (conv == 'c')
		return (ft_putchar_fd(va_arg(*ap, int), 1));
	if (conv == 's')
		return (ft_putstr_fd(va_arg(*ap, char *), 1));
	if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fd(va_arg(*ap, int), 1));
	if (conv == 'u')
		return (ft_putnbr_u_fd(va_arg(*ap, int), 1));
	if (conv == 'x')
		return (ft_putnbr_base_fd(va_arg(*ap, int), "0123456789abcdef", 1));
	if (conv == 'X')
		return (ft_putnbr_base_fd(va_arg(*ap, int), "0123456789ABCDEF", 1));
	if (conv == 'p')
		return (ft_putptr_fd(va_arg(*ap, unsigned long), 1));
	if (conv == '%')
		return (ft_putchar_fd('%', 1));
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
