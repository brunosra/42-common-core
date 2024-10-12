/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:48:41 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/11 10:20:47 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !ft_is_simulation_finished(philo->table))
		printf(WH"%-6ld"RST" %d has taken the 1st fork 1️⃣🍴[%d] \n", elapsed, philo->id, philo->first_fork->fork_id);
	if (status == TAKE_SECOND_FORK && !ft_is_simulation_finished(philo->table))
		printf(WH"%-6ld"RST" %d has taken the 2nd fork 2️⃣🍴[%d] \n", elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !ft_is_simulation_finished(philo->table))
		printf(WH"%-6ld"RST" %d is eating 🍝 [%ld] \n", elapsed, philo->id, philo->meals_c);
	else if (status == SLEEPING && !ft_is_simulation_finished(philo->table))
		printf(WH"%-6ld"RST" %d is sleeping 😴 \n", elapsed, philo->id);
	else if (status == THINKING && !ft_is_simulation_finished(philo->table))
		printf(WH"%-6ld"RST" %d is thinking 💭 \n", elapsed, philo->id);
	else if (status == DEAD)
		printf(RD"%-6ld %d is dead 💀 \n"RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = ft_gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !ft_is_simulation_finished(philo->table))
			printf(MG"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !ft_is_simulation_finished(philo->table))
			printf(YL"%-6ld"RST" %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !ft_is_simulation_finished(philo->table))
			printf(BL"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !ft_is_simulation_finished(philo->table))
			printf(GR"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (status == DEAD)
			printf(RD"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}