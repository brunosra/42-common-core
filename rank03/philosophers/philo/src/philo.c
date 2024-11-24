/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:11:27 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/24 11:59:21 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		ft_throw_error("Usage: <philos_nbr> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[meals_nbr]", NULL, 0);
		return (0);
	}
	if (ft_parse_args_to_table(&table, argv) == 0)
		return (2);
	if (ft_parse_philo_and_forks(&table) == 0)
		return (3);
	if (ft_init_philo_threads(&table) == 0)
		return (4);
	ft_start_monitor(&table);
	ft_throw_error(NULL, &table, 3);
	return (1);
}
