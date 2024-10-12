/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:29 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/11 10:02:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_and_quit(const char *msg)
{
	printf(RD"%s\n"RST, msg);
	exit(EXIT_FAILURE);
}

void	precise_usleep(long	usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_gettime(MICROSECOND);
	while (ft_gettime(MICROSECOND) - start < usec)
	{
		if (ft_is_simulation_finished(table))
			break;
		elapsed = ft_gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (ft_gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

long	ft_gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_error_and_quit("Gettimeofday error");
	if (time_code == SECOND)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_error_and_quit("Wrong input gettime");
	return (1337);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}