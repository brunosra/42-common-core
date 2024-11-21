/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:11:10 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/21 20:59:10 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_mutexes(t_table *table, int error_stage)
{
	int	i;

	i = 0;
	if (error_stage >= 2 && table->forks)
	{
		while (i < table->nbr_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (error_stage >= 1)
	{
		pthread_mutex_destroy(&table->start_mtx);
		pthread_mutex_destroy(&table->print_mtx);
		pthread_mutex_destroy(&table->eat_mtx);
		pthread_mutex_destroy(&table->end_mtx);
	}
}

static void	ft_cleanup(t_table *table, int error_stage)
{
	int	i;

	i = -1;
	if (error_stage >= 1 && table->philo)
	{
		while (++i < table->nbr_philos)
		{
			if (error_stage >= 3)
			{
				if (pthread_join(table->philo[i].thread, NULL))
				{
					ft_throw_error("Failed to join thread", table, 2);
					return ;
				}
			}
		}
		free(table->philo);
	}
	if (error_stage >= 2)
		ft_destroy_mutexes(table, error_stage);
}

int	ft_throw_error(char *str, t_table *table, int error_stage)
{
	if (str != NULL)
		printf(RD"[ERROR]: "RST"%s\n", str);
	if (error_stage)
		ft_cleanup(table, error_stage);
	return (0);
}
