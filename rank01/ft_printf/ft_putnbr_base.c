/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:00:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/05/03 10:19:52 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr_base(int n, char *base)
{
	size_t	i;
	size_t	count;
	size_t	base_len;

	base_len = ft_strlen(base);
	i = (unsigned int) n;
	count = 0;
	if (i < base_len)
		count += ft_putchar(base[i % base_len]);
	else
	{
		count += ft_putnbr_base(i / base_len, base);
		count += ft_putnbr_base(i % base_len, base);
	}
	return (count);
}
