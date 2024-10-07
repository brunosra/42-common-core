/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:17:12 by bschwell          #+#    #+#             */
/*   Updated: 2024/02/05 23:08:47 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	trim_s;
	size_t	trim_e;

	trim_s = 0;
	trim_e = 0;
	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	while (s1[trim_s] && ft_strchr(set, s1[trim_s]))
		trim_s++;
	while (ft_strchr(set, s1[ft_strlen(s1) - trim_e - 1]))
		trim_e++;
	trimmed_str = ft_substr(s1, trim_s, ft_strlen(s1) - trim_s - trim_e);
	if (!trimmed_str)
		return (NULL);
	trimmed_str[ft_strlen(s1) - trim_s - trim_e + 1] = 0;
	return (trimmed_str);
}
