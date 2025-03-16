/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:01:27 by bschwell          #+#    #+#             */
/*   Updated: 2025/02/27 03:27:50 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_all(int argcount, ...)
{
	va_list	ap;
	char	*tmp;
	char	*to_free;
	char	*curr_str;
	int		curr_arg;

	curr_arg = 0;
	tmp = malloc(1);
	if (!tmp)
		return (NULL);
	tmp[0] = 0;
	va_start(ap, argcount);
	while (curr_arg++ < argcount)
	{
		curr_str = va_arg(ap, char *);
		to_free = tmp;
		tmp = ft_strjoin(tmp, curr_str);
		free(to_free);
	}
	va_end(ap);
	return (tmp);
}
