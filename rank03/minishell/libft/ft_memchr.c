/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:29:45 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/28 18:28:16 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	const unsigned char	*ptr_src;
	size_t				i;
	unsigned char		f;

	ptr_src = (const unsigned char *)src;
	i = 0;
	f = (unsigned char)c;
	while (i < n)
	{
		if (ptr_src[i] == f)
			return ((void *)&ptr_src[i]);
		i++;
	}
	return (NULL);
}
