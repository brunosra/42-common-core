/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_handle_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:48:45 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/10 02:28:23 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_is_valid_file(char *filepath, int mode);
static int	ft_check_file_access(char *filepath, int mode);
static int	ft_file_error(char *filepath, char *msg, int code);
void		ft_remove_created_files(t_node *node);
void		ft_create_files(t_node *node);

/**
 * @brief  Checks if the given file is valid and accessible for the specified
 * mode.
 * 
 * @param  filepath  Path to the file.
 * @param  mode      Access mode to check (e.g., read, write, execute).
 * @return int       Status code.
 **         0 if the file is valid.
 **         127 if the file does not exist.
 **         126 if it is a directory or lacks necessary permissions.
 */
int	ft_is_valid_file(char *filepath, int mode)
{
	struct stat	file_stat;

	if (!filepath)
		return (ft_file_error(NULL, "syntax error near unexpected token "
				"`newline'", 1));
	if (stat(filepath, &file_stat) == -1)
		return (ft_file_error(filepath, "No such file or directory", 127));
	if (S_ISDIR(file_stat.st_mode))
		return (ft_file_error(filepath, "Is a directory", 126));
	return (ft_check_file_access(filepath, mode));
}

/**
 * @brief  Handles file-related error messages and returns the appropriate error
 * code.
 * 
 * @param  filepath  Path to the file.
 * @param  msg       Error message to display.
 * @param  code      Error code to return.
 * @return int       Always returns the provided error code.
 */
static int	ft_file_error(char *filepath, char *msg, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (filepath)
		ft_putstr_fd(filepath, STDERR_FILENO);
	ft_putstr_three_fd(": ", msg, "\n", STDERR_FILENO);
	return (code);
}

/**
 * @brief  Checks the file's access permissions based on the requested mode.
 * 
 * @param  filepath  Path to the file.
 * @param  mode      Access mode to check.
 * @return int       Status code (0 if valid, 126 if permission denied).
 */
static int	ft_check_file_access(char *filepath, int mode)
{
	if (mode == X_OK)
	{
		if (access(filepath, X_OK) == -1)
			return (ft_file_error(filepath, "Permission denied", 126));
		return (0);
	}
	if (mode == O_RDONLY)
	{
		if (access(filepath, R_OK) == -1)
			return (ft_file_error(filepath, "Permission denied", 126));
		return (0);
	}
	if (mode == O_WRONLY || mode == (O_WRONLY | O_CREAT)
		|| mode == (O_WRONLY | O_APPEND))
	{
		if (access(filepath, W_OK) == -1 && errno != ENOENT)
			return (ft_file_error(filepath, "Permission denied", 126));
	}
	return (0);
}

/**
 * @brief  Creates files for output redirection nodes if they don't already
 * exist.
 * 
 * @param  node  Pointer to the node in the AST containing the out redirection.
 */
void	ft_create_files(t_node *node)
{
	int	fd;

	if (!node)
		return ;
	if (node->token->type == TKN_OUT_RD && node->right
		&& node->right->token->value && node->file == false)
	{
		if (ft_strcmp(node->token->value, ">>") == 0)
			fd = open(node->right->token->value,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(node->right->token->value,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
		else
			perror("open");
	}
	if (node->left && node->left->token->type == TKN_OUT_RD)
		ft_create_files(node->left);
}

/**
 * @brief  Removes created files if they are empty.
 * 
 * This function traverses the AST and deletes files that were created
 * during execution, ensuring that only empty files are removed.
 * 
 * @param  node  Pointer to the AST node.
 */
void	ft_remove_created_files(t_node *node)
{
	struct stat	file_stat;

	if (!node)
		return ;
	if (node->file == true && node->file_unlink == false)
	{
		if (stat(node->right->token->value, &file_stat) == 0
			&& file_stat.st_size == 0)
		{
			if (unlink(node->right->token->value) == -1)
				perror("unlink");
			node->file_unlink = true;
		}
	}
	ft_remove_created_files(node->right);
	ft_remove_created_files(node->left);
}
