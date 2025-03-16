/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:04:22 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/05/01 16:37:10 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*ptr;
	size_t	len_dst;
	size_t	len_src;

	ptr = dst;
	len_dst = 0;
	len_src = 0;
	while (*ptr && size)
	{
		ptr++;
		len_dst++;
		size--;
	}
	len_src = ft_strlen(src);
	while (*src && size > 1)
	{
		*ptr++ = *src++;
		size--;
	}
	if (size == 1 || *src == '\0')
		*ptr = '\0';
	return (len_dst + len_src);
}
