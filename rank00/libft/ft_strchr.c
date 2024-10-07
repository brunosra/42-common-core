/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:23:53 by bschwell          #+#    #+#             */
/*   Updated: 2024/04/09 20:11:42 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	char	cc;

	cc = (char) c;
	p = (char *) s;
	while (*p != 0)
	{
		if (*p == cc)
			return (p);
		p++;
	}
	if (cc == 0)
		return (p);
	return (NULL);
}
