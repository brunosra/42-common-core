/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:11:38 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/24 11:59:19 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_args_to_table(t_table *table, char **argv)
{
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoll(argv[2], 0, 0);
	table->time_to_eat = ft_atoll(argv[3], 0, 0);
	table->time_to_sleep = ft_atoll(argv[4], 0, 0);
	if (table->nbr_philos < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
		return (ft_throw_error("Try values bigger than 0!\n", NULL, 0));
	if (argv[5])
	{
		table->nbr_meals = ft_atoll(argv[5], 0, 0);
		if (table->nbr_meals <= 0)
			return (ft_throw_error("Try values bigger than 0!\n", NULL, 0));
	}
	else
		table->nbr_meals = -1;
	table->nbr_philos_full = 0;
	table->start_dinner = ft_get_time();
	table->end_dinner = 0;
	table->philo = NULL;
	table->forks = NULL;
	return (1);
}

int	ft_init_philos_n_forks(t_table *table, int i)
{
	table->philo[i].id = i + 1;
	table->philo[i].right_fork = i;
	table->philo[i].left_fork = (i + 1) % table->nbr_philos;
	table->philo[i].table = table;
	table->philo[i].count_meals = 0;
	table->philo[i].time_last_meal = table->start_dinner;
	if (pthread_mutex_init(&table->forks[i], NULL))
		return (ft_throw_error("Mutex init fails\n", table, 1));
	return (1);
}

int	ft_init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->start_mtx, NULL))
		return (ft_throw_error("Mutex failed\n", table, 1));
	if (pthread_mutex_init(&table->end_mtx, NULL))
		return (ft_throw_error("Mutex failed\n", table, 1));
	if (pthread_mutex_init(&table->print_mtx, NULL))
		return (ft_throw_error("Mutex failed\n", table, 1));
	if (pthread_mutex_init(&table->eat_mtx, NULL))
		return (ft_throw_error("Mutex failed\n", table, 1));
	return (1);
}

int	ft_parse_philo_and_forks(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->nbr_philos);
	if (table->philo == NULL)
		return (ft_throw_error("malloc fails\n", table, 0));
	table->forks = malloc(sizeof(t_mtx) * table->nbr_philos);
	if (table->forks == NULL)
		return (ft_throw_error("malloc fails\n", table, 1));
	while (i < table->nbr_philos)
	{
		ft_init_philos_n_forks(table, i);
		i++;
	}
	return (ft_init_mutexes(table));
}
