/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:54:53 by bschwell          #+#    #+#             */
/*   Updated: 2024/05/25 17:48:18 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[len] = 0;
	return (sub);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	len = ft_strlen((char *) s) + 1;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == 0)
		return (ft_strdup(s2));
	if (len_s2 == 0)
		return (ft_strdup(s1));
	sub = malloc(len_s1 + len_s2 + 1);
	if (!sub)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len_s1)
		sub[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		sub[i++] = s2[j++];
	sub[i] = 0;
	return (sub);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void	free_and_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}
