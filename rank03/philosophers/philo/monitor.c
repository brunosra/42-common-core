/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:07:41 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/11 10:04:11 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (ft_get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ft_gettime(MILLISECOND) - ft_get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;

	if (elapsed > t_to_die) // time to die has to be converted to milliseconds
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *) data;
	while (!all_threads_are_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!ft_is_simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !ft_is_simulation_finished(table))
		{
			if (ft_philo_died(table->philos + i))
			{
				ft_set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DEAD, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}