/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 02:54:19 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/07 03:42:16 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strtok(char *str, const char *delim);
int		ft_exec_builtins_check(t_node *node, t_minishell *ms);
int		ft_exec_builtins(t_node *node, t_minishell *ms);

/**
 * @brief 	Tokenize a string and returns them in order
 * 
 * @param 	str 	String to be tokenized
 * @param 	delim 	Token delimiter
 * @return 	char* 	Pointer to the first char of the first pointer.
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*start;

	if (str != NULL)
		last = str;
	else if (last == NULL)
		return (NULL);
	while (*last && strchr(delim, *last) != NULL)
		last++;
	if (*last == '\0')
	{
		last = NULL;
		return (NULL);
	}
	start = last;
	while (*last && strchr(delim, *last) == NULL)
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (start);
}

/**
 * @brief 	Check if builtin executed correctly
 * 
 * @param 	node	tree node
 * @param 	ms 		minishell pointer
 * @return 	int 
 ** 	  	0 in case of success
 **			N (any number) in case of error
 */
int	ft_exec_builtins_check(t_node *node, t_minishell *ms)
{
	if (!ft_strcmp(node->token->value, "exit"))
		return (ft_free_ms(ms, true, true, ft_exit_code(-1)));
	if (!ft_strcmp(node->token->value, "pwd")
		|| !ft_strcmp(node->token->value, "env"))
		return (ft_free_ms(ms, true, true, 0));
	else if (!ft_strcmp(node->token->value, "cd"))
		return (ft_free_ms(ms, true, true,
				ft_builtin_cd_check(node->cmd_ready, ms)));
	else if (!ft_strcmp(node->token->value, "export"))
		ft_builtin_export_check(node->cmd_ready);
	ft_free_ms(ms, true, true, 0);
	return (EX_OK);
}

/**
 * @brief 	Executes builtin if check allows
 * 
 * @param 	node 	tree node
 * @param 	ms 		minishell ptr
 * @return 	int 	exit code that was in the ms struct
 */
int	ft_exec_builtins(t_node *node, t_minishell *ms)
{
	if (!ft_strcmp(node->token->value, "echo"))
	{
		ft_builtin_echo(node->cmd_ready);
		ft_free_ms(ms, true, true, 0);
	}
	else if (!ft_strcmp(node->token->value, "exit"))
		ft_builtin_exit(node->cmd_ready);
	else if (!ft_strcmp(node->token->value, "env"))
		ft_builtin_env(node->cmd_ready, ms);
	else if (!ft_strcmp(node->token->value, "pwd"))
		ft_builtin_pwd();
	else if (!ft_strcmp(node->token->value, "cd"))
		ft_builtin_cd(node->cmd_ready, ms);
	else if (!ft_strcmp(node->token->value, "export"))
		ft_builtin_export(node->cmd_ready, ms);
	else if (!ft_strcmp(node->token->value, "unset"))
		ft_builtin_unset(node->cmd_ready, ms);
	return (ft_exit_code(-1));
}
