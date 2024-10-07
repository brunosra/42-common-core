/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:00:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/07/02 20:44:12 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr_base_fd(int n, char *base, int fd)
{
	size_t	i;
	size_t	count;
	size_t	base_len;

	base_len = ft_strlen(base);
	i = (unsigned int) n;
	count = 0;
	if (i < base_len)
		count += ft_putchar_fd(base[i % base_len], fd);
	else
	{
		count += ft_putnbr_base_fd(i / base_len, base, fd);
		count += ft_putnbr_base_fd(i % base_len, base, fd);
	}
	return (count);
}
