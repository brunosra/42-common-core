/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:31:27 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/11/08 23:38:49 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[i] && n > 0)
	{
		ptr[i] = str[i];
		i++;
		n--;
	}
	ptr[i] = '\0';
	return (ptr);
}
