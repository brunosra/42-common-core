/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:26:23 by bschwell          #+#    #+#             */
/*   Updated: 2024/02/10 17:15:32 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*s;
	char	*d;

	s = (char *) src;
	d = dst;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && *s != '\0')
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
	*d = '\0';
	return (ft_strlen(src));
}
