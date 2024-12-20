/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:10:31 by bschwell          #+#    #+#             */
/*   Updated: 2024/11/24 11:59:19 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "colors.h"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			right_fork;
	int			left_fork;
	long long	count_meals;
	long long	time_last_meal;
	pthread_t	thread;
	t_table		*table;

}			t_philo;

typedef struct s_table
{
	t_philo		*philo;
	int			nbr_philos;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	nbr_meals;
	int			end_dinner;
	long long	start_dinner;
	int			nbr_philos_full;
	t_mtx		*forks;
	t_mtx		start_mtx;
	t_mtx		eat_mtx;
	t_mtx		end_mtx;
	t_mtx		print_mtx;
}				t_table;

int			ft_throw_error(char *str, t_table *table, int error_stage);
int			ft_atoi(const char *ptr);
long long	ft_atoll(char *str, int i, long long res);
long long	ft_get_time(void);
int			ft_parse_args_to_table(t_table *table, char **argv);
int			ft_init_philos_n_forks(t_table *table, int i);
int			ft_init_mutexes(t_table *table);
int			ft_parse_philo_and_forks(t_table *table);
int			ft_init_philo_threads(t_table *table);
void		ft_sleep_for_action(t_philo *philo, long long va_time_ms,
				char *action, char*color);
void		*ft_start_dinner(void *data);
int			ft_is_dinner_over(t_table *table);
void		ft_start_monitor(t_table *table);
