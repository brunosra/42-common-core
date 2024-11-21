/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:55:06 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:55 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		ft_handle_error("Error\nUsage: <philos_nbr>"
			"<time_to_die> <time_to_eat> <time_to_sleep>"
			"[meals_nbr]\n", NULL, 0);
	ft_parsing_args_to_table(&table, argv);
	ft_parsing_philo_and_forks(&table);
	ft_init_philo_threads(&table);
	ft_start_monitor(&table);
	ft_handle_error(NULL, &table, 3);
	return (0);
}
