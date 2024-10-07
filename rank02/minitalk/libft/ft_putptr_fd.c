/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:00:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/07/02 20:56:04 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

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

int	ft_putptr_fd(unsigned long ptr, int fd)
{
	int	count;

	count = 0;
	if (ptr == 0)
		count += ft_putstr("(nil)");
	else
	{
		count += ft_putstr_fd("0x", fd);
		count += ft_putnbr_base_ptr_fd(ptr, "0123456789abcdef", fd);
	}
	return (count);
}
