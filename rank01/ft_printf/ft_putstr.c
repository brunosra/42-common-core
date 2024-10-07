/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:22:24 by bschwell          #+#    #+#             */
/*   Updated: 2024/04/27 09:31:50 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	long long int	i;

	i = 0;
	if (str == NULL)
	{
		return (ft_putstr("(null)"));
	}
	while (*str)
		i += ft_putchar(*str++);
	return (i);
}
