/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:27:32 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/14 03:43:56 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_builtin_cd(char **args, t_minishell *ms);
static void	ft_cd_set_resolved_p(char **args, char *curpwd, char *res_p,
				t_minishell *ms);
void		ft_resolve_rel_p(const char *base_p, const char *rel_p,
				char *res_p);
static void	ft_resolve_tilde(const char *rel_p, char *tmp_p);
static char	*ft_norm_pth(char *tmp_p, char *norm_p);

/**
 * @brief  Implements the `cd` built-in command, updating environment variables.
 * 
 * @param  args  Command arguments.
 * @param  ms    Pointer to the minishell structure.
 * @return void  Changes the directory and updates environment variables.
 */
void	ft_builtin_cd(char **args, t_minishell *ms)
{
	char	*curpwd;
	char	res_p[PATH_MAX];

	ft_memset(res_p, 0, PATH_MAX);
	curpwd = ft_get_env("PWD", ms);
	if (curpwd == NULL)
	{
		ft_exit_code(errno);
		return ;
	}
	ft_cd_set_resolved_p(args, curpwd, res_p, ms);
	ft_set_env("OLDPWD", curpwd, ms);
	ft_set_env("PWD", res_p, ms);
	ft_strlcpy(ms->currpath, res_p, ft_strlen(res_p) + 1);
	chdir(ms->currpath);
	ft_exit_code(0);
}

/**
 * @brief  Resolves the tilde (`~`) expansion in a relative path.
 * 
 * @param  rel_p  The relative path containing `~` at the beginning.
 * @param  tmp_p  Buffer to store the expanded path.
 * @return void   Modifies `tmp_p` in place with the resolved path.
 */
static void	ft_resolve_tilde(const char *rel_p, char *tmp_p)
{
	if (rel_p[1] == '\0')
		ft_strncpy(tmp_p, getenv("HOME"), PATH_MAX - 1);
	else
	{
		ft_strncpy(tmp_p, getenv("HOME"), PATH_MAX - 1);
		tmp_p[PATH_MAX - 1] = '\0';
		ft_strncat(tmp_p, rel_p + 1, PATH_MAX - ft_strlen(tmp_p) - 1);
	}
}

/**
 * @brief	resolve relative paths for cd
 * 
 * @param	base_p 		the current working directory
 * @param	rel_p 		relative path to solve to
 * @param	res_p 		pointer to where to store the resolved path
 */
void	ft_rsolve_rel_p(const char *base_p, const char *rel_p, char *res_p)
{
	char		tmp_p[PATH_MAX];
	char		norm_pth[PATH_MAX];

	ft_memset(norm_pth, 0, PATH_MAX);
	ft_memset(tmp_p, 0, PATH_MAX);
	if (rel_p[0] == '~')
	{
		ft_resolve_tilde(rel_p, tmp_p);
	}
	else if (rel_p[0] == '/')
		ft_strncpy(tmp_p, rel_p, PATH_MAX - 1);
	else
	{
		ft_strncpy(tmp_p, base_p, PATH_MAX - 1);
		tmp_p[PATH_MAX - 1] = '\0';
		if (tmp_p[strlen(tmp_p) - 1] != '/')
			ft_strncat(tmp_p, "/", PATH_MAX - ft_strlen(tmp_p) - 1);
		ft_strncat(tmp_p, rel_p, PATH_MAX - ft_strlen(tmp_p) - 1);
	}
	ft_strncpy(res_p, ft_norm_pth(tmp_p, norm_pth), PATH_MAX - 1);
	res_p[PATH_MAX - 1] = '\0';
}

/**
 * @brief  Resolves the target path for the `cd` command based on arguments.
 * 
 * @param  args    Command arguments.
 * @param  curpwd  Current working directory.
 * @param  res_p   Buffer to store the resolved path.
 * @param  ms      Pointer to the minishell structure.
 * @return void    Updates `res_p` with the resolved path.
 */
static void	ft_cd_set_resolved_p(char **args, char *curpwd, char *res_p,
				t_minishell *ms)
{
	if (args[1] == NULL)
		ft_strncpy(res_p, ft_get_env("HOME", ms), PATH_MAX - 1);
	else if (args[2] == NULL)
	{
		if (!ft_strcmp(args[1], "-"))
		{
			if (!ft_get_env("OLDPWD", ms))
			{
				ft_exit_code(errno);
				return ;
			}
			ft_strncpy(res_p, ft_get_env("OLDPWD", ms), PATH_MAX - 1);
			printf("%s\n", res_p);
		}
		else if (!ft_strcmp(args[1], "~"))
			ft_strncpy(res_p, ft_get_env("HOME", ms), PATH_MAX - 1);
		else
			ft_rsolve_rel_p(curpwd, args[1], res_p);
	}
}

/**
 * @brief 			Normatizes path
 * 
 * @param tmp_p		Temporary path from main function.
 * @param norm_p 	Normatized path pointer from main function.
 * @return char* 	Pointer to the normatized path.
 */
static char	*ft_norm_pth(char *tmp_p, char *norm_p)
{
	char		*token;

	ft_strncpy(norm_p, "/", PATH_MAX - 1);
	token = ft_strtok(tmp_p, "/");
	while (token != NULL)
	{
		if (ft_strcmp(token, ".") == 0)
			;
		else if (ft_strcmp(token, "..") == 0)
		{
			if (ft_strrchr(norm_p, '/') != NULL
				&& ft_strrchr(norm_p, '/') != norm_p)
				*(ft_strrchr(norm_p, '/')) = '\0';
			else
				norm_p[1] = '\0';
		}
		else
		{
			if (ft_strlen(norm_p) > 1 && norm_p[ft_strlen(norm_p) - 1] != '/')
				ft_strncat(norm_p, "/", PATH_MAX - ft_strlen(norm_p) - 1);
			ft_strncat(norm_p, token, PATH_MAX - ft_strlen(norm_p) - 1);
		}
		token = ft_strtok(NULL, "/");
	}
	return (norm_p);
}
