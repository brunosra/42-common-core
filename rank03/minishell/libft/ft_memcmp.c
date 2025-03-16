/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:39:28 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/28 18:28:46 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*ptr_str1;
	unsigned char	*ptr_str2;
	size_t			i;

	ptr_str1 = (unsigned char *)str1;
	ptr_str2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ptr_str1[i] != ptr_str2[i])
			return (ptr_str1[i] - ptr_str2[i]);
		if (i == n - 1)
			break ;
		i++;
	}
	if ((ptr_str1[i] && ptr_str2[i] == '\0' && i < n)
		|| (ptr_str1[i] == '\0' && ptr_str2[i] && i < n))
		return (ptr_str1[i] - ptr_str2[i]);
	return (0);
}
