/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:31:57 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 17:49:35 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		//parse the input and fill table
		parse_input(&table, argv);
		//creating all philos, forks, etc.
		//start simulation
		//clean all ==> philos full or 1 philo died
	}
	else
	{
		ft_error_and_quit("[BAD INPUT] "RST
			CY"Usage:"RST" nbr_of_philos time_to_die"
			" time_to_eat time_to_sleep [max_times_philo_can_eat]");
	}
}
