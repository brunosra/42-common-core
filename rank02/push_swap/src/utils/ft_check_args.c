/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:08:20 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_check_longs_dups(long *arr, int total_arr)
{
	int	i;
	int	j;

	i = -1;
	while (++i < total_arr)
	{
		j = -1;
		if (arr[i] >= INT_MIN && arr[i] <= INT_MAX)
		{
			while (++j < total_arr)
				if (arr[i] == arr[j] && i != j)
					return (0);
		}
		else
			return (0);
	}
	return (1);
}

static int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == 0)
		return (0);
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_nums(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		if (!ft_check_str(arr[i]))
			return (0);
	return (1);
}

static int	ft_count_words(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i++])
		count++;
	return (count);
}

int	ft_check_args(char *arg_str)
{
	char	**str_arr;
	int		i;
	int		total_num;
	long	*long_arr;

	i = 0;
	if (ft_strlen(arg_str) == 0)
		return (0);
	str_arr = ft_split(arg_str, ' ');
	total_num = ft_count_words(str_arr);
	if (!ft_check_nums(str_arr))
		return (ft_free_arr(str_arr));
	long_arr = (long *) malloc(sizeof(long) * total_num + 1);
	i = -1;
	while (str_arr[++i])
		long_arr[i] = ft_atol(str_arr[i]);
	ft_free_arr(str_arr);
	if (!ft_check_longs_dups(long_arr, total_num))
	{
		free(long_arr);
		return (0);
	}
	free(long_arr);
	return (1);
}
