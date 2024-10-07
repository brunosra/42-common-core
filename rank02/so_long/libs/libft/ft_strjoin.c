/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:17:12 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/15 10:48:58 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(s2));
	if (ft_strlen(s2) == 0)
		return (ft_strdup(s1));
	sub = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s1, ft_strlen(s1));
	ft_memcpy(sub + ft_strlen(s1), s2, ft_strlen(s2));
	sub[ft_strlen(s1) + ft_strlen(s2)] = 0;
	return (sub);
}
