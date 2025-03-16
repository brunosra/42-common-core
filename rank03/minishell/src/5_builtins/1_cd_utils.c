/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:27:32 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/07 03:44:37 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_builtin_cd_check(char **args, t_minishell *ms);
static int	ft_cd_set_resolved_p_check(char **args, char *curpwd,
				char *res_p, t_minishell *ms);

/**
 * @brief  Determines and sets the resolved path for the `cd` command.
 * 
 * @param  args   Array of arguments passed to `cd`.
 * @param  curpwd Current working directory.
 * @param  res_p  Buffer to store the resolved path.
 * @param  ms     Pointer to the minishell structure.
 * @return int    Status of the path resolution.
 **         0 on success.
 **         1 if `HOME` or `OLDPWD` is not set.
 **         2 if too many arguments are passed.
 */
static int	ft_cd_set_resolved_p_check(char **args, char *curpwd,
				char *res_p, t_minishell *ms)
{
	if (args[1] == NULL)
	{
		if (ft_get_env("HOME", ms) == NULL)
			return (ft_putstr_and_return("minishell: cd: HOME not set\n", 1));
		ft_strncpy(res_p, ft_get_env("HOME", ms), PATH_MAX - 1);
	}
	else if (args[2] == NULL)
	{
		if (!ft_strcmp(args[1], "-"))
		{
			if (ft_get_env("OLDPWD", ms) == NULL)
				return (ft_putstr_and_return("minishell: cd: OLDPWD not set\n",
						2));
			ft_strncpy(res_p, ft_get_env("OLDPWD", ms), PATH_MAX - 1);
		}
		else
			ft_rsolve_rel_p(curpwd, args[1], res_p);
	}
	else
		return (ft_putstr_and_return("minishell: cd: too many arguments\n", 1));
	return (0);
}

/**
 * @brief  Handles error checking and execution of the `cd` built-in command.
 * 
 * @param  args  Array of arguments passed to `cd`.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Status of the `cd` execution.
 **         0 on success.
 **         1 if `getcwd` fails or path resolution fails.
 **         1 if the target directory does not exist.
 **         Returns specific error codes from `ft_cd_set_resolved_p_check`.
 */
int	ft_builtin_cd_check(char **args, t_minishell *ms)
{
	char	*curpwd;
	char	res_p[PATH_MAX];
	int		ret;

	curpwd = ft_get_env("PWD", ms);
	if (curpwd == NULL)
	{
		printf("getcwd error\n");
		return (ft_putstr_and_return("getcwd:\n", errno));
	}
	ret = ft_cd_set_resolved_p_check(args, curpwd, res_p, ms);
	if (ret != 0)
		return (ret);
	if (chdir(res_p) != 0)
		return (ft_putstr_three_fd("minishell: cd: ", args[1],
				": No such file or directory\n", STDERR_FILENO));
	return (0);
}
