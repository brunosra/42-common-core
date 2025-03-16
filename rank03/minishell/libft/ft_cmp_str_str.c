/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_str_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:49:12 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 19:22:12 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cmp_str_str(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	j = 0;
	n = 0;
	if (lit[0] == '\0')
		return (0);
	while (big[i] && i < len)
	{
		n = i;
		while (big[i + j] == lit[j] && big[i + j] && n < len)
		{
			if (lit[j + 1] == '\0')
				return (1);
			j++;
			n++;
		}
		j = 0;
		i++;
	}
	return (0);
}
