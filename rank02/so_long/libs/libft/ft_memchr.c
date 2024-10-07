/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:22:21 by bschwell          #+#    #+#             */
/*   Updated: 2024/01/31 20:05:10 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;
	char	cc;

	cc = (char) c;
	p = (char *) s;
	while (n)
	{
		if (*p == cc)
			return (p);
		p++;
		n--;
	}
	return (NULL);
}
