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
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
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

void		ft_error_and_quit(const char *msg);
void		parse_input(t_table *table, char **argv);
void		*safe_malloc(size_t bytes);
static void	handle_mutex_error(int status, t_opcode cd);
void		safe_mutex_handle(t_mtx *mutex,t_opcode cd);
static void	handle_thread_error(int status, t_opcode cd);
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode cd);

#endif