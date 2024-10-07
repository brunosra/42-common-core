/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 05:15:25 by bschwell          #+#    #+#             */
/*   Updated: 2024/02/05 23:04:50 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_chars(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	i;
	char		*str_n;
	size_t		len;

	i = n;
	len = ft_count_chars(n);
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	str_n = malloc((len * sizeof(char)) + 1);
	if (!str_n)
		return (NULL);
	str_n[len] = 0;
	if (i == 0)
		str_n[0] = '0';
	while (i)
	{
		str_n[--len] = '0' + (i % 10);
		i /= 10;
	}
	if (n < 0)
		str_n[0] = '-';
	return (str_n);
}
