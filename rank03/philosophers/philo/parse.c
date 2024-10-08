/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:31:45 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 17:46:24 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*ft_valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_error_and_quit("[ERROR] "RST"Only positive numbers are acceptable");
	if (!ft_is_digit(*str))
		ft_error_and_quit("[ERROR] "RST"Input is not a number");
	nbr = str;
	while (ft_is_digit(*str++))
		len++;
	if (len > 10)
		ft_error_and_quit("[ERROR] "RST"Input is greater than MAX_INT");
	return (nbr);
}

static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (ft_is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		ft_error_and_quit("[ERROR] "RST"Input is greater than MAX_INT");
	return (num);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		ft_error_and_quit("[ERROR] "RST"Timestamps must be larger than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
