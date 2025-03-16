/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 04:38:05 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/09 00:59:06 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
t_minishell	*ft_ms_struct(t_minishell *ms, int flag);
static char	*ft_free_inputs(char *s1, char *s2, int free_s1, int free_s2);
void		ft_print_ast(t_node *node, int depth);

/**
 * @brief  Joins two strings and optionally frees them.
 * 
 * This function concatenates `s1` and `s2` into a new dynamically allocated 
 * string. It also provides an option to free `s1` and/or `s2` after joining.
 * 
 * @param  s1       First string to join.
 * @param  s2       Second string to join.
 * @param  free_s1  If true, frees `s1` after joining.
 * @param  free_s2  If true, frees `s2` after joining.
 * @return char*    Newly allocated concatenated string or NULL on failure.
 */
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (ft_free_inputs(s1, s2, free_s1, free_s2));
	if (s1)
		ft_strlcpy(joined, s1, len1 + 1);
	if (s2)
		ft_strlcat(joined, s2, len1 + len2 + 1);
	ft_free_inputs(s1, s2, free_s1, free_s2);
	return (joined);
}

/**
 * @brief Manages the global minishell structure.
 * 
 * If the flag is set, it returns the stored pointer. Otherwise, it updates
 * the stored pointer to the given minishell structure.
 * 
 * @param ms    Pointer to the minishell structure (if updating).
 * @param flag  If nonzero, retrieves the stored pointer.
 * @return t_minishell*  The global minishell structure pointer.
 */
t_minishell	*ft_ms_struct(t_minishell *ms, int flag)
{
	static t_minishell	*ptr;

	if (flag)
		return (ptr);
	ptr = ms;
	return (ptr);
}

/**
 * @brief  Frees input strings based on flags.
 * 
 * @param  s1       First string.
 * @param  s2       Second string.
 * @param  free_s1  If true, frees `s1`.
 * @param  free_s2  If true, frees `s2`.
 * @return NULL     Always returns NULL for easier error handling.
 */
static char	*ft_free_inputs(char *s1, char *s2, int free_s1, int free_s2)
{
	if (free_s1 && s1)
		free(s1);
	if (free_s2 && s2)
		free(s2);
	return (NULL);
}

/**
 * For testing. 
 * @brief  Recursively prints the Abstract Syntax Tree (AST) structure for
 * debugging.
 * 
 * @param  node   Pointer to the current node in the AST.
 * @param  depth  Current depth level for indentation.
 */
void	ft_print_ast(t_node *node, int depth)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!node)
		return ;
	while (++i < depth)
		printf("  ");
	if (node->cmd_ready)
	{
		printf("Node Type: %d, Value:", node->token->type);
		while (node->cmd_ready[j])
		{
			printf(" %i_%s", j, node->cmd_ready[j]);
			j++;
		}
		printf("\n");
	}
	else
		printf("Node Type: %d, Value: %s\n", node->token->type,
			node->token->value);
	ft_print_ast(node->left, depth + 1);
	ft_print_ast(node->right, depth + 1);
}
