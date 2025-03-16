/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:35:45 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/03 01:13:04 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_process_export(char *str, t_minishell *ms);
static int	ft_export_add_var(char *arg, t_minishell *ms);
static char	**ft_expand_list(char **list, char *new_var);
static int	ft_replace_existing_var(char **list, char *arg);

/**
 * @brief  Processes and adds a valid export variable.
 * 
 * @param  str  The export argument.
 * @param  ms   Pointer to the minishell structure.
 * @return int  1 if successfully processed, 0 otherwise.
 */
int	ft_process_export(char *str, t_minishell *ms)
{
	if (!str)
		return (0);
	return (ft_export_add_var(str, ms));
}

/**
 * @brief  Adds a variable to the appropriate list (envp or export).
 *         If the variable exists, updates its value.
 * 
 * @param  arg  The variable assignment (e.g., "VAR=VALUE").
 * @param  ms   Pointer to the minishell structure.
 * @return int  0 on success.
 */
static int	ft_export_add_var(char *arg, t_minishell *ms)
{
	int	replaced;

	if (ft_strchr(arg, '='))
	{
		replaced = ft_replace_existing_var(ms->env.envp, arg);
		if (replaced == 0)
			ms->env.envp = ft_expand_list(ms->env.envp, arg);
		replaced = ft_replace_existing_var(ms->env.export, arg);
		if (replaced == 0)
			ms->env.export = ft_expand_list(ms->env.export, arg);
	}
	else
	{
		replaced = ft_replace_existing_var(ms->env.export, arg);
		if (replaced == 0)
			ms->env.export = ft_expand_list(ms->env.export, arg);
	}
	return (0);
}

/**
 * @brief  Expands the given environment or export list to add a new variable.
 * 
 * @param  list     The environment or export list.
 * @param  new_var  The new variable to add.
 * @return char**   Pointer to the updated list, or NULL on failure.
 */
static char	**ft_expand_list(char **list, char *new_var)
{
	char	**new_list;
	int		count;
	int		i;

	count = 0;
	while (list[count])
		count++;
	new_list = malloc((count + 2) * sizeof(char *));
	if (!new_list)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_list[i] = list[i];
		i++;
	}
	new_list[count] = ft_strdup(new_var);
	if (!new_list[count])
		return (NULL);
	new_list[count + 1] = NULL;
	free(list);
	return (new_list);
}

/**
 * @brief  Replaces an existing variable in the given list with a new value.
 * If the var exists and is reassigned without a value, it remains unchanged.
 * 
 * @param  list  Environment or export list.
 * @param  arg   The variable assignment (e.g., "VAR=VALUE").
 * @return int   1 if replaced, 0 if not found, -1 on error.
 */
static int	ft_replace_existing_var(char **list, char *arg)
{
	int		i;
	size_t	len;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		len = equal_sign - arg;
	else
		len = ft_strlen(arg);
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(list[i], arg, len)
			&& (list[i][len] == '=' || list[i][len] == '\0'))
		{
			if (!equal_sign && ft_strchr(list[i], '='))
				return (1);
			free(list[i]);
			list[i] = ft_strdup(arg);
			if (!list[i])
				return (-1);
			return (1);
		}
	}
	return (0);
}
