/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:30:50 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/09 11:39:37 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_bool(t_mtx *mutex, bool *dest, bool val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	ft_get_bool(t_mtx *mutex, bool *val)
{
	bool	ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	ft_set_long(t_mtx *mutex, long *dest, long val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

long	ft_get_long(t_mtx *mutex, long *val)
{
	long	ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	ft_is_simulation_finished(t_table *table)
{
	return (ft_get_bool(&table->table_mutex, &table->end_simulation));
}
