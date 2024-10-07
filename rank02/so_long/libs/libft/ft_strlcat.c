/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:11:27 by bschwell          #+#    #+#             */
/*   Updated: 2024/02/05 23:09:21 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (size == 0)
		return (s_len);
	if (d_len >= size)
		return (s_len + size);
	dst += d_len;
	size -= d_len;
	while (*src && --size)
		*dst++ = *src++;
	*dst = 0;
	return (d_len + s_len);
}
