/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:34:04 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/15 08:24:19 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long int	i;
	size_t		count;

	i = n;
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
