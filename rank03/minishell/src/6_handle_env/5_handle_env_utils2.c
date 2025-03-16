/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_handle_env_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:55:07 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/03 06:56:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_set_env(const char *key, const char *value, t_minishell *ms);
static char	**ft_expand_envp(char **envp, char *new_var);

/**
 * @brief  Sets or updates an environment variable in the environment array.
 * 
 * @param  key    Variable name to set or update.
 * @param  value  Value to assign to the variable.
 * @param  ms     Pointer to the minishell structure.
 * @return int    Status of the operation.
 **         0 on success.
 **         1 on error.
 */
int	ft_set_env(const char *key, const char *value, t_minishell *ms)
{
	int		i;
	size_t	len;
	char	*new_var;

	if (!key || !value || !ms || !ms->env.envp)
		return (1);
	len = ft_strlen(key);
	new_var = ft_strjoin_all(3, key, "=", value);
	if (!new_var)
		return (1);
	i = -1;
	while (ms->env.envp[++i])
	{
		if (!ft_strncmp(ms->env.envp[i], key, len)
			&& ms->env.envp[i][len] == '=')
		{
			free(ms->env.envp[i]);
			ms->env.envp[i] = new_var;
			return (0);
		}
	}
	ms->env.envp = ft_expand_envp(ms->env.envp, new_var);
	if (!ms->env.envp)
		return (1);
	return (0);
}

/**
 * @brief      Expands the environment variable array by adding a new variable.
 *
 * @param      envp     The array of strings representing environment variables.
 * @param      new_var  The new environment variable to be added (in "KEY=VALUE"
   format).
 * @return     The updated environment array, or NULL in case of allocation
   failure.
 */
static char	**ft_expand_envp(char **envp, char *new_var)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc((count + 2) * sizeof(char *));
	if (!new_envp)
	{
		free(new_var);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}
