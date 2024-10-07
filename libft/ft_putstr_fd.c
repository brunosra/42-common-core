/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:34:04 by bschwell          #+#    #+#             */
/*   Updated: 2024/07/03 15:32:38 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	long long int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_putstr_fd("(null)", fd));
	}
	while (*s)
		i += ft_putchar_fd(*s++, fd);
	return (i);
}
