/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_replace_var_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:09:47 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/05 00:08:36 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_replace_str(char **value, char *key, char *ptr, char *env_value);
static char	*ft_create_replaced_str(char *start, char *env_value, char *end);
int			ft_cleanup(char *to_free1, char *to_free2, int error);
static int	ft_replace_entire_str(char **value, char *env_value);
int			ft_check_balanced_quotes(char *str, int idx);

/**
 * @brief  Replaces a substring in a string with a new value.
 * 
 * @param  value      Pointer to the string to modify.
 * @param  key        Substring (key) to replace.
 * @param  ptr        Pointer to the position of the key in the string.
 * @param  env_value  New value to replace the key with.
 * @return int        Status of the replacement.
 **         0 on success.
 **         1 on error.
 */
int	ft_replace_str(char **value, char *key, char *ptr, char *env_value)
{
	char	*start;
	char	*end;
	char	*new_value;

	if (!value || !*value || !key || !ptr || !env_value)
		return (1);
	if (ft_strlen(*value) == ft_strlen(key) + 1)
		return (ft_replace_entire_str(value, env_value));
	start = ft_substr(*value, 0, ptr - *value);
	if (*env_value != '\0' || (*env_value == '\0'
			&& ptr[ft_strlen(key) + 1] != ' '))
		end = ft_strdup(ptr + ft_strlen(key) + 1);
	else
		end = ft_strdup(ptr + ft_strlen(key) + 2);
	if (!start || !end)
		return (ft_cleanup(start, end, 1));
	new_value = ft_create_replaced_str(start, env_value, end);
	if (!new_value)
		return (1);
	free(*value);
	*value = new_value;
	return (0);
}

/**
 * @brief  Creates a new string replacing the target substring.
 * 
 * @param  start      Start part of the string.
 * @param  env_value  New value to insert.
 * @param  end        End part of the string.
 * @return char*      Newly allocated string with replacement.
 */
static char	*ft_create_replaced_str(char *start, char *env_value, char *end)
{
	char	*new_value;
	size_t	new_len;

	new_len = ft_strlen(start) + ft_strlen(env_value) + ft_strlen(end) + 1;
	new_value = malloc(new_len);
	if (!new_value)
	{
		ft_cleanup(start, end, 1);
		return (NULL);
	}
	ft_strlcpy(new_value, start, new_len);
	ft_strlcat(new_value, env_value, new_len);
	ft_strlcat(new_value, end, new_len);
	ft_cleanup(start, end, 0);
	return (new_value);
}

/**
 * @brief  Cleans up allocated memory in case of failure.
 * 
 * @param  start  Start part of the string.
 * @param  end    End part of the string.
 * @param  error  1 if returning an error, 0 otherwise.
 * @return int    Always returns the error parameter.
 */
int	ft_cleanup(char *to_free1, char *to_free2, int error)
{
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	return (error);
}

/**
 * @brief  Replaces the entire string when it's fully equal to the key.
 * 
 * @param  value      Pointer to the string to modify.
 * @param  env_value  New value to replace the key with.
 * @return int        0 on success.
 */
static int	ft_replace_entire_str(char **value, char *env_value)
{
	char	*new_value;

	new_value = ft_strdup(env_value);
	free(*value);
	*value = new_value;
	return (0);
}

/**
 * @brief  Checks if the quotes in a string are balanced up to a specific index.
 * 
 * @param  str  String to check.
 * @param  idx  Index up to which the string should be checked.
 * @return int  Boolean indicating whether the quotes are balanced.
 **         1 if balanced.
 **         0 otherwise.
 */
int	ft_check_balanced_quotes(char *str, int idx)
{
	int		i;
	char	quote_type;
	int		is_balanced;

	i = 0;
	quote_type = '\0';
	is_balanced = 1;
	while (i < idx && str[i])
	{
		ft_verify_quotes(&quote_type, str[i]);
		i++;
	}
	if (quote_type != '\0')
		is_balanced = 0;
	return (is_balanced);
}
