/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:00:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/04/27 17:05:04 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr(int n, int uint)
{
	long int	i;
	size_t		count;

	if (!uint)
		i = n;
	else
		i = (unsigned int) n;
	count = 0;
	if (i < 0)
	{
		count += ft_putchar('-');
		i *= -1;
	}
	if (i < 10)
		count += ft_putchar((i % 10) + '0');
	else
	{
		count += ft_putnbr(i / 10, 0);
		count += ft_putnbr(i % 10, 0);
	}
	return (count);
}
