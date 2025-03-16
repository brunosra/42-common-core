/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:57:40 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/11 06:32:15 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_has_error_file(t_minishell *ms, char *file);
void	ft_add_error_file(t_minishell *ms, char *file);
void	ft_sleep(void);

/**
 * @brief  Checks if the given file is already in the error list.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @param  file  Name of the file to check.
 * @return int  1 if the file is already in the list, 0 otherwise.
 */
int	ft_has_error_file(t_minishell *ms, char *file)
{
	int	i;

	if (!ms->error_files)
	{
		ft_sleep();
		return (0);
	}
	i = 0;
	while (ms->error_files[i])
	{
		if (!ft_strcmp(ms->error_files[i], file))
			return (1);
		i++;
	}
	ft_sleep();
	return (0);
}

/**
 * @brief  Adds a file to the error list to avoid duplicate messages.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @param  file  Name of the file to add.
 */
void	ft_add_error_file(t_minishell *ms, char *file)
{
	int		i;
	char	**new_list;

	i = 0;
	while (ms->error_files && ms->error_files[i])
		i++;
	new_list = malloc(sizeof(char *) * (i + 2));
	if (!new_list)
		return ;
	i = 0;
	while (ms->error_files && ms->error_files[i])
	{
		new_list[i] = ms->error_files[i];
		i++;
	}
	new_list[i] = ft_strdup(file);
	new_list[i + 1] = NULL;
	free(ms->error_files);
	ms->error_files = new_list;
}

void	ft_sleep(void)
{
	int	i;
	int	wait;

	i = 0;
	wait = 100000;
	while (i != wait)
		i++;
}
