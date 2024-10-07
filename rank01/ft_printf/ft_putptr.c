/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:00:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/05/03 10:18:35 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_putnbr_base_ptr(unsigned long ptr, char *base)
{
	size_t			count;
	size_t			base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (ptr < base_len)
		count += ft_putchar(base[ptr % base_len]);
	else
	{
		count += ft_putnbr_base_ptr(ptr / base_len, base);
		count += ft_putnbr_base_ptr(ptr % base_len, base);
	}
	return (count);
}

int	ft_putptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		count += ft_putstr("(nil)");
	else
	{
		count += ft_putstr("0x");
		count += ft_putnbr_base_ptr(ptr, "0123456789abcdef");
	}
	return (count);
}
