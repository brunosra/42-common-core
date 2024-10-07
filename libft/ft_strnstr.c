/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:28:00 by bschwell          #+#    #+#             */
/*   Updated: 2024/01/28 16:28:02 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_l;
	char	*b;
	char	*l;

	b = (char *) big;
	l = (char *) little;
	len_l = ft_strlen(l);
	if (len_l == 0)
		return (b);
	while (*b && len >= len_l)
	{
		if (ft_memcmp(b, l, len_l) == 0)
			return (b);
		b++;
		len--;
	}
	return (NULL);
}
