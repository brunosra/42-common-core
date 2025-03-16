/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:37:03 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/05/01 16:38:36 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] == str2[i])
			i++;
		else
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	if ((str1[i] == '\0' && str2[i] && i < n)
		|| (str1[i] && str2[i] == '\0' && i < n))
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
