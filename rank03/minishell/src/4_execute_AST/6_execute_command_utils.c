/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_execute_command_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 03:00:36 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/15 15:07:16 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_find_executable(t_minishell *ms, char *cmd);
static char	**ft_get_path_dirs(t_minishell *ms);
static int	ft_build_executable_path(t_minishell *ms, char *dir, char *cmd);

/**
 * @brief  Searches for an executable file in the system PATH.
 * 
 * This function retrieves the system's PATH environment variable, splits it 
 * into directories, and iterates through them to check if the given command 
 * exists and is executable. If found, it updates the `full_path` in `ms->env`.
 * 
 * @param  ms   Pointer to the minishell structure containing environment vars.
 * @param  cmd  Command to search for in the PATH.
 * @return int  Status of the search.
 **         0 if the executable is found and updated in `ms->env.full_path`.
 **         127 if not found or if the PATH is invalid.
 */
int	ft_find_executable(t_minishell *ms, char *cmd)
{
	int	i;
	int	result;

	ms->env.paths = ft_get_path_dirs(ms);
	if (!ms->env.paths)
		return (127);
	i = 0;
	while (ms->env.paths[i])
	{
		result = ft_build_executable_path(ms, ms->env.paths[i], cmd);
		if (result == 0)
			return (0);
		i++;
	}
	ft_free_split(ms->env.paths);
	return (127);
}

/**
 * @brief  Retrieves and splits the system PATH into directories.
 * 
 * @param  ms   Pointer to the minishell structure.
 * @return char** Array of directories in PATH or NULL if not found.
 */
static char	**ft_get_path_dirs(t_minishell *ms)
{
	if (!ft_get_env("PATH", ms))
		return (NULL);
	ms->env.env_paths = ft_get_env("PATH", ms);
	if (!ms->env.env_paths)
		return (NULL);
	return (ft_split(ms->env.env_paths, ':'));
}

/**
 * @brief  Constructs the full path for an executable and checks if it exists.
 * 
 * @param  ms   Pointer to the minishell structure.
 * @param  dir  Directory from PATH to check.
 * @param  cmd  Command name to append to the directory.
 * @return int  0 if the executable is found, 127 otherwise.
 */
static int	ft_build_executable_path(t_minishell *ms, char *dir, char *cmd)
{
	ms->env.full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!ms->env.full_path)
	{
		ft_free_split(ms->env.paths);
		return (127);
	}
	ft_strcpy(ms->env.full_path, dir);
	ft_strcat(ms->env.full_path, "/");
	ft_strcat(ms->env.full_path, cmd);
	if (access(ms->env.full_path, X_OK) == 0)
	{
		ft_free_split(ms->env.paths);
		return (0);
	}
	free(ms->env.full_path);
	return (127);
}
