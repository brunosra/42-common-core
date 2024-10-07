/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:19 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/08 19:37:49 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

char	*add_char2str(char *str, char c, int pid)
{
	char	*new_str;
	size_t	str_len;
	size_t	i;

	i = 0;
	if (str == NULL)
	{
		new_str = (char *) malloc(sizeof(char));
		new_str[0] = '\0';
		str_len = 0;
	}
	else
		str_len = ft_strlen(str);
	new_str = (char *) malloc((str_len + 2) * sizeof(char));
	while (i < str_len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free (str);
	kill(pid, SIGUSR1);
	return (new_str);
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ctx)
{
	static int		curr_bit;
	static char		curr_char;
	static char		*msg;

	(void) ctx;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		if (sig == SIGUSR1)
			curr_char |= (1 << curr_bit);
	curr_bit++;
	if (curr_bit == 8)
	{
		if (curr_char == '\0')
		{
			ft_printf("%s\n", msg);
			free(msg);
			msg = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		else
			msg = add_char2str(msg, curr_char, info->si_pid);
		curr_bit = 0;
		curr_char = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_handle_sig;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
}
