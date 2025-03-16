/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:13:42 by bschwell          #+#    #+#             */
/*   Updated: 2025/02/26 06:38:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_builtin_pwd(void);

/**
 * @brief	pwd - print name of current/working directory
 * 
 * @param 	ms minishell pointer
 * @return 	int 
 */
int	ft_builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd: ");
		return (errno);
	}
}
