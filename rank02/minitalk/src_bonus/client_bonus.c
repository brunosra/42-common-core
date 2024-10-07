/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:37:40 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/08 19:56:28 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <bits/types.h>
#include <unistd.h>
#include "../libft/libft.h"

static int	ft_print_error(char *msg)
{
	ft_printf("\033[0;31m%s\033[0m", "[ERROR] ");
	ft_printf("%s\n", msg);
	return (1);
}

void	ft_sendchar(char c, int bit, int pid)
{
	if ((((c >> bit) & 1) && 1) == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

void	ft_send_msg(int pid, char *msg)
{
	static int				i = 0;
	static char				*tmp_msg;
	static int				bit = 0;

	if (msg != NULL)
		tmp_msg = msg;
	if (tmp_msg[i] != 0)
	{
		ft_sendchar(tmp_msg[i], bit, pid);
		if (++bit == 8)
		{
			bit = 0;
			i++;
		}
	}
	else
	{
		if (bit < 8)
		{
			kill(pid, SIGUSR2);
			bit++;
		}
	}
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ctx)
{
	(void) ctx;
	if (sig == SIGUSR2)
		(exit(EXIT_SUCCESS));
	if (sig == SIGUSR1)
		ft_send_msg(info->si_pid, NULL);
}

int	main(int argc, char **argv)
{
	size_t				i;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_handle_sig;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	if (argc != 3)
		return (ft_print_error("Usage: ./client [pid_server] [string_msg]"));
	else
	{
		i = 0;
		while (argv[1][i] != 0)
			if (!ft_isdigit(argv[1][i++]))
				return (ft_print_error("[pid_server] must be numeric."));
		ft_send_msg(atoi(argv[1]), argv[2]);
	}
	while (1)
		pause();
}
