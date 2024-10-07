/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:17:12 by bschwell          #+#    #+#             */
/*   Updated: 2024/04/13 15:40:52 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_curr_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static int	ft_count_strs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	*free_all(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		n_strs;
	int		i;

	if (!s)
		return (NULL);
	n_strs = ft_count_strs(s, c);
	strs = malloc(sizeof(char *) * (n_strs + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			strs[i] = ft_substr(s, 0, ft_curr_word_len(s, c));
			if (!strs[i++])
				return (free_all(strs));
			s += ft_curr_word_len(s, c);
		}
		else
			s++;
	}
	strs[n_strs] = NULL;
	return (strs);
}
