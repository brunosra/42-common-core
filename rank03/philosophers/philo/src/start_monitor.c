/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:23 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/11/21 19:47:57 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_philo_full(t_philo *philo)
{
	t_table	*table;
	int		result;

	table = philo->table;
	result = 0;
	pthread_mutex_lock(&table->eat_mtx);
	if (table->n_meals != -1 && philo->count_meals >= table->n_meals)
	{
		pthread_mutex_unlock(&table->eat_mtx);
		pthread_mutex_lock(&table->end_mtx);
		table->n_philos_full++;
		if (table->n_philos_full >= table->n_philo)
		{
			table->end_dinner = 1;
			result = 1;
		}
		pthread_mutex_unlock(&table->end_mtx);
	}
	else
		pthread_mutex_unlock(&table->eat_mtx);
	return (result);
}

static int	ft_check_philo_status(t_philo *philo)
{
	t_table		*table;
	long long	now_time;

	table = philo->table;
	pthread_mutex_lock(&table->eat_mtx);
	now_time = ft_get_time();
	if (now_time - philo->time_last_meal >= table->time_to_die)
	{
		ft_sleep_for_action(philo, 0, "died");
		pthread_mutex_unlock(&table->eat_mtx);
		pthread_mutex_lock(&table->end_mtx);
		table->end_dinner = 1;
		pthread_mutex_unlock(&table->end_mtx);
		return (1);
	}
	pthread_mutex_unlock(&table->eat_mtx);
	if (ft_check_philo_full(philo))
		return (1);
	return (0);
}

void	ft_start_monitor(t_table *table)
{
	int	i;
	int	monitor;

	monitor = 1;
	while (monitor)
	{
		i = 0;
		table->n_philos_full = 0;
		while (i < table->n_philo)
		{
			if (monitor && ft_check_philo_status(&table->philo[i]))
			{
				monitor = 0;
				break ;
			}
			i++;
		}
		usleep(100);
	}
}

int	ft_check_end_dinner(t_table *table)
{
	int	ended;

	pthread_mutex_lock(&table->end_mtx);
	ended = table->end_dinner;
	pthread_mutex_unlock(&table->end_mtx);
	return (ended);
}
