/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 07:44:25 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static char	*ft_subs_space(char *str)
{
	int		i;
	int		j;
	char	*spaces;

	i = -1;
	spaces = "\n\t\v\f\r";
	while (str[++i])
	{
		j = -1;
		while (spaces[++j])
			if (str[i] == spaces[j])
				str[i] = ' ';
	}
	return (str);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static char	*ft_trimarg(char *s)
{
	char	*ptr;

	ptr = NULL;
	while (ft_isspace(*s))
		s++;
	ptr = s + ft_strlen(s) - 1;
	while (ft_isspace(*ptr))
		*ptr-- = 0;
	return (s);
}

char	*ft_join_args(int argc, char **argv)
{
	int		total_size;
	int		i;
	char	*str;
	char	*ptr_str;

	i = 0;
	total_size = argc - 1;
	while (argv[++i])
		total_size += ft_strlen(ft_trimarg(argv[i]));
	str = (char *) malloc(total_size);
	ptr_str = str;
	i = 0;
	while (argv[++i])
	{
		ft_memcpy(ptr_str, ft_trimarg(argv[i]), ft_strlen(ft_trimarg(argv[i])));
		ptr_str += ft_strlen(ft_trimarg(argv[i]));
		if (i == argc - 1)
			*ptr_str = '\0';
		else
			*ptr_str++ = ' ';
	}
	return (ft_subs_space(str));
}
