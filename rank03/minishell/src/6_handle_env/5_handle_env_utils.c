/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_handle_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:17:28 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/07 05:14:46 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_duplicate_envp(char **envp);
char	*ft_get_env_value(const char *str, t_minishell *ms, char **key,
			bool heredoc);
char	*ft_get_env(const char *key, t_minishell *ms);
int		ft_unset_env(const char *key, char **list);

/**
 * @brief  Duplicates the environment variables array.
 * 
 * @param  envp  Array of environment variables to duplicate.
 * @return char**  Pointer to the newly allocated duplicate of `envp`.
 **         NULL if memory allocation fails.
 */
char	**ft_duplicate_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = ft_calloc(sizeof(char *), (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			ft_free_split(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

/**
 * @brief  Extracts the value of an environment variable from a given string.
 * 
 * @param  str  String containing the variable name (e.g., `$VAR`).
 * @param  ms   Pointer to the minishell structure.
 * @param  key  Pointer to store the extracted variable name.
 * @param heredoc Bool to indicate whether it is for a heredoc or not.
 * @return char*  Value of the environment variable.
 **         NULL if the variable does not exist.
 */
char	*ft_get_env_value(const char *str, t_minishell *ms, char **key,
							bool heredoc)
{
	int		i;
	char	*value;
	int		start;
	char	**envp;

	envp = ms->env.envp;
	if (!str || !envp)
		return (NULL);
	i = 1;
	start = i;
	if (str[i] && (!ft_isalnum(str[i]) && heredoc == true))
	{
		*key = ft_strdup(str);
		return (*key);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*key = ft_substr(str, start, i - start);
	if (!*key)
		return (NULL);
	value = ft_get_env(*key, ms);
	return (value);
}

/**
 * @brief  Retrieves the value of an environment var from the environment array.
 * 
 * @param  key  Variable name to search for.
 * @param  ms   Pointer to the minishell structure.
 * @return char*  Pointer to the value of the variable.
 **         NULL if the variable does not exist.
 */
char	*ft_get_env(const char *key, t_minishell *ms)
{
	int		i;
	size_t	len;
	char	**envp;

	envp = ms->env.envp;
	len = ft_strlen(key);
	i = 0;
	if (!key || !envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
		{
			if (envp[i][len + 1])
				return (&envp[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief  Unsets (removes) an environment variable from the environment array.
 * 
 * @param  key  Variable name to remove.
 * @param  ms   Pointer to the minishell structure.
 * @return int  Status of the operation.
 **         0 on success.
 **         1 if the variable does not exist or on error.
 */
int	ft_unset_env(const char *key, char **list)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	j = 0;
	if (!key || !list)
		return (1);
	while (list[i])
	{
		if (!ft_strncmp(list[i], key, len))
		{
			free(list[i]);
			j = i - 1;
			while (list[++j])
				list[j] = list[j + 1];
			return (0);
		}
		i++;
	}
	return (1);
}
