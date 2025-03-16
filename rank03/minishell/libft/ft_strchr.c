/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:22:38 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/05/01 16:32:14 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	char			*ptr;
	unsigned char	equal_c;

	i = 0;
	ptr = NULL;
	equal_c = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == equal_c)
		{
			ptr = (char *)&str[i];
			return (ptr);
		}
		i++;
	}
	if (equal_c == '\0')
		return (ptr = (char *)&str[i]);
	return (ptr);
}
