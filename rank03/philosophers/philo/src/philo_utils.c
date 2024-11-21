/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:11:21 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/21 20:11:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *ptr)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	sig = 1;
	res = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			sig = -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		res *= 10;
		res += (ptr[i] - '0');
		i++;
	}
	return (res * sig);
}

long long	ft_atoll(char *str, int i, long long res)
{
	int	sig;

	sig = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LLONG_MAX / 10)
			|| (res == LLONG_MAX / 10 && (str[i] - '0') > (LLONG_MAX % 10)))
		{
			if (sig == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sig);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}
