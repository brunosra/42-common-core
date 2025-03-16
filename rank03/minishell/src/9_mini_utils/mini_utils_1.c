/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 04:38:05 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/07 22:34:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_perror(char *error, int return_value);
int	ft_putstr_and_return(char *msg, int return_value);
int	ft_exit_code(int newcode);
int	ft_putstr_three_fd(const char *s1, const char *s2, const char *s3, int fd);
int	ft_last_left_is_cmd(t_node *node);

/**
 * @brief  Print an error message using perror and return a specified value.
 * 
 * @param  error         The error message to display.
 * @param  return_value  The value to return after displaying the error.
 * @return int           The specified return value.
 */
int	ft_perror(char *error, int return_value)
{
	perror(error);
	return (return_value);
}

/**
 * @brief  Print a message to STDERR and return a specified value.
 * 
 * @param  msg           The message to display.
 * @param  return_value  The value to return after displaying the message.
 * @return int           The specified return value.
 */
int	ft_putstr_and_return(char *msg, int return_value)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (return_value);
}

/**
 * @brief  Manages the global exit code of the shell.
 * 
 * This function acts as a getter and setter for the exit code.
 * If called with -1, it returns the current exit code.
 * Otherwise, it updates the exit code to the given value.
 * 
 * @param  newcode  The new exit code to set (-1 to retrieve current value).
 * @return int      The updated or current exit code.
 */
int	ft_exit_code(int newcode)
{
	static int	code = 0;

	if (newcode == -1)
		return (code);
	code = newcode;
	return (code);
}

/**
 * @brief Writes three strings consecutively to the given file descriptor.
 * 
 * @param s1  First string.
 * @param s2  Second string.
 * @param s3  Third string.
 * @param fd  File descriptor to write to.
 */
int	ft_putstr_three_fd(const char *s1, const char *s2, const char *s3, int fd)
{
	if (s1)
		write(fd, s1, ft_strlen(s1));
	if (s2)
		write(fd, s2, ft_strlen(s2));
	if (s3)
		write(fd, s3, ft_strlen(s3));
	return (1);
}

/**
 * @brief Checks if the last left node before NULL is a command node.
 * 
 * @param node  Pointer to the starting node.
 * @return int  1 if the last node before NULL is a command, 0 otherwise.
 */
int	ft_last_left_is_cmd(t_node *node)
{
	t_node	*current;

	if (!node)
		return (0);
	current = node;
	while (current->left && current->left->token->type != TKN_NULL)
		current = current->left;
	if (current->token->type == TKN_CMD)
		return (1);
	return (0);
}
