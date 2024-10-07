/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:23:17 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

long int	ft_atol(const char *nptr)
{
	char		*ptr;
	long int	s;
	long int	r;

	r = 0;
	s = 1;
	ptr = (char *) nptr;
	while (*ptr == '\f' || *ptr == '\n' || *ptr == '\r'
		|| *ptr == '\t' || *ptr == '\v' || *ptr == ' ')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			s = -1;
		ptr++;
	}
	while (*ptr && ft_isdigit(*ptr))
	{
		r += *ptr - '0';
		if (ft_isdigit(*(ptr + 1)) && ft_isdigit(*ptr))
			r *= 10;
		ptr++;
	}
	return (r * s);
}
