/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bschwell <bschwell@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/15 11:21:27 by bschwell		  #+#	#+#			 */
/*   Updated: 2024/10/08 16:08:30 by bschwell		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include "colors.h"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_c;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

# define DEBUG_MODE 1

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}	t_philo_status;

void		ft_error_and_quit(const char *msg);
void		parse_input(t_table *table, char **argv);
void		ft_init_data(t_table *table);
void		*safe_malloc(size_t bytes);
void		safe_mutex_handle(t_mtx *mutex,t_opcode cd);
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode cd);
void		ft_set_bool(t_mtx *mutex, bool *dest, bool val);
bool		ft_get_bool(t_mtx *mutex, bool *val);
void		ft_set_long(t_mtx *mutex, long *dest, long val);
long		ft_get_long(t_mtx *mutex, long *val);
bool		ft_is_simulation_finished(t_table *table);
void		wait_all_threads(t_table *table);
long		ft_gettime(t_time_code time_code);
void		precise_usleep(long	usec, t_table *table);
void		write_status(t_philo_status status, t_philo *philo, bool debug);
void		dinner_start(t_table *table);
void		*monitor_dinner(void *data);
bool		all_threads_are_running(t_mtx *mutex, long *threads, long philo_nbr);
void		increase_long(t_mtx *mutex, long *value);
void		think(t_philo *philo, bool pre_simulation);
void		clean(t_table *table);
void		de_synchronize_philos(t_philo *philo);

#endif