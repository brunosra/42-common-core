/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:17:12 by bschwell          #+#    #+#             */
/*   Updated: 2024/02/05 23:58:24 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_res;
	int		i;

	if (!s || !f)
		return (NULL);
	str_res = malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (!str_res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str_res[i] = f(i, s[i]);
		i++;
	}
	str_res[i] = 0;
	return (str_res);
}
