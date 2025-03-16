/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:49:12 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/28 18:39:37 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*search_in_string(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		n = i;
		while (big[i + j] == lit[j] && big[i + j] && n < len)
		{
			if (lit[j + 1] == '\0')
				return ((char *)big + i);
			j++;
			n++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	if (lit[0] == '\0')
		return ((char *)big);
	return (search_in_string(big, lit, len));
}
