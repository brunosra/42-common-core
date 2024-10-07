/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:34:04 by bschwell          #+#    #+#             */
/*   Updated: 2024/07/03 15:38:01 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	long long int	i;

	if (s == NULL)
		return (ft_putstr_fd("(null)\n", fd));
	while (*s)
		i += ft_putchar_fd(*s++, fd);
	i += ft_putchar_fd('\n', fd);
	return (i);
}
