/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:18:13 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/15 15:06:35 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_free_ms(t_minishell *ms, bool free_prompt, bool free_envp, int exit);
void	ft_free_tokens(t_token *tokens);
void	ft_free_ast(t_node *root);
void	ft_free_split(char **str);

/**
 * @brief  Frees the memory allocated for the minishell.
 * 
 * @param  tokens  Pointer to the t_minishell to free.
 */
int	ft_free_ms(t_minishell *ms, bool free_prompt, bool free_envp, int exit)
{
	ft_free_tokens(ms->tokens);
	ft_free_ast(ms->ast_root);
	if (ms->error_files)
		ft_free_split(ms->error_files);
	free(ms->input);
	if (free_prompt == true)
		free(ms->prompt);
	if (free_envp == true)
	{
		ft_free_split(ms->env.envp);
		if (ms->env.export)
			ft_free_split(ms->env.export);
	}
	return (exit);
}

/**
 * @brief  Frees the memory allocated for the token array.
 * 
 * @param  tokens  Pointer to the array of tokens to free.
 */
void	ft_free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i].value && tokens[i].type != TKN_NULL)
	{
		free(tokens[i].value);
		if (tokens[i].old_value)
			free(tokens[i].old_value);
		i++;
	}
	free(tokens);
	return ;
}

/**
 * @brief  Frees the memory allocated for the abstract syntax tree (AST).
 * 
 * @param  root  Pointer to the root of the AST to free.
 */
void	ft_free_ast(t_node *root)
{
	if (!root)
		return ;
	if (root->left)
		ft_free_ast(root->left);
	if (root->right)
		ft_free_ast(root->right);
	ft_free_split(root->cmd_ready);
	root->cmd_ready = NULL;
	root->token = NULL;
	if (root->heredoc_stops)
	{
		free(root->heredoc_stops);
		root->heredoc_stops = NULL;
	}
	free(root);
	return ;
}

/**
 * @brief  Frees the memory allocated for a split string array.
 * 
 * @param  str  Pointer to the array of strings to free.
 */
void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	while (--i >= 0)
		free(str[i]);
	free(str);
	str = NULL;
}
