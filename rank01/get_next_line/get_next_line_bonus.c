/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:54:55 by bschwell          #+#    #+#             */
/*   Updated: 2024/05/25 17:50:56 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*read_fd(int fd, char *rest, char *buf)
{
	char	*tmp_rest;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!rest)
			rest = ft_strdup("");
		tmp_rest = rest;
		rest = ft_strjoin(tmp_rest, buf);
		free(tmp_rest);
		if (ft_strchr(rest, '\n') != NULL)
			break ;
	}
	return (rest);
}

static char	*process_rest(char *l_read)
{
	long int	l_size;
	char		*rest;

	l_size = 0;
	while (l_read[l_size] != '\0' && l_read[l_size] != '\n')
		l_size++;
	if (l_read[l_size] == '\0')
		return (NULL);
	rest = ft_substr(l_read, l_size + 1, ft_strlen(l_read) - l_size);
	if (rest[0] == '\0')
	{
		free(rest);
		rest = NULL;
	}
	if (ft_strchr(l_read, '\n'))
		l_read[l_size + 1] = '\0';
	else
		l_read[l_size] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*fds[OPEN_MAX];
	char		*line;
	char		*buf;

	buf = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (buf == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(fds[fd]);
		free(buf);
		return (NULL);
	}
	line = read_fd(fd, fds[fd], buf);
	free(buf);
	if (line == NULL)
	{
		free(fds[fd]);
		fds[fd] = NULL;
		return (NULL);
	}
	fds[fd] = process_rest(line);
	return (line);
}
