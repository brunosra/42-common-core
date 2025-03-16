/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:32:03 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/26 00:43:09 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			j;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	j = n;
	if (!dest && !src && n != 0)
		return (0);
	while (j > 0)
	{
		ptr_dest[j - 1] = ptr_src[j - 1];
		j--;
	}
	return (dest);
}
