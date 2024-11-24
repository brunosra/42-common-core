/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:10:49 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/24 11:57:39 by bschwell         ###   ########.fr       */
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
	if (table->nbr_meals != -1 && philo->count_meals >= table->nbr_meals)
	{
		pthread_mutex_unlock(&table->eat_mtx);
		pthread_mutex_lock(&table->end_mtx);
		table->nbr_philos_full++;
		if (table->nbr_philos_full >= table->nbr_philos)
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
		ft_sleep_for_action(philo, 0, "died", RD);
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
		table->nbr_philos_full = 0;
		while (i < table->nbr_philos)
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

int	ft_is_dinner_over(t_table *table)
{
	int	ended;

	pthread_mutex_lock(&table->end_mtx);
	ended = table->end_dinner;
	pthread_mutex_unlock(&table->end_mtx);
	return (ended);
}
