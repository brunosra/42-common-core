/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:51:52 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/11 10:02:04 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		ft_error_and_quit("[ERROR] "RST"Error with malloc");
	return (ret);
}

static void handle_mutex_error(int status, t_opcode cd)
{
	if (0 == status)
		return ;
	if (status == EINVAL && (cd == LOCK || cd == UNLOCK || cd == DESTROY))
		ft_error_and_quit("[ERROR] "RST"The value specified by mutex is invalid");
	else if (status == EINVAL && cd == INIT)
		ft_error_and_quit("[ERROR] "RST"The value specified by attr is invalid");
	else if (status == EPERM)
		ft_error_and_quit("[ERROR] "RST"The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		ft_error_and_quit("[ERROR] "RST"The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		ft_error_and_quit("[ERROR] "RST"Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex,t_opcode cd)
{
	if (cd == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), cd);
	else if (cd == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), cd);
	else if (cd == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), cd);
	else if (cd == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), cd);
	else
		ft_error_and_quit("[ERROR] "RST"Wrong opcode for mutex handle");
}

static void handle_thread_error(int status, t_opcode cd)
{
	if (0 == status)
		return ;
	if (status == EAGAIN)
		ft_error_and_quit("[ERROR] "RST"No resources to create another thread");
	else if (status == EPERM)
		ft_error_and_quit("[ERROR] "RST"The caller does not have appropriate permission");
	else if (status == EINVAL && cd == CREATE)
		ft_error_and_quit("[ERROR] "RST"The value specified by attr is invalid");
	else if (status == EINVAL && (cd == JOIN || cd == DETACH))
		ft_error_and_quit("[ERROR] "RST"The value specified by thread cannot be joined");
	else if (status == ESRCH)
		ft_error_and_quit("[ERROR] "RST"No thread could be found corresponding to that.");
	else if (status == EDEADLK)
		ft_error_and_quit("[ERROR] "RST"A deadlock was detected.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode cd)
{
	if (cd == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), cd);
	else if (cd == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), cd);
	else if (cd == DETACH)
		handle_thread_error(pthread_detach(*thread), cd);
	else
		ft_error_and_quit("[ERROR] "RST"Wrong opcode for thread handle: use <CREATE> <JOIN> <DETACH>");
}
