/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_game_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:02:24 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 14:17:06 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	ft_free_map_and_error(t_map *map)
{
	ft_print_err(ERROR_READ);
	ft_free_map_and_exit(map);
}

void	ft_create_game_map(char *file, t_map *map)
{
	char	*line;
	char	*map_str;
	char	*tmp_line;
	int		fd;
	int		lines_total;

	map_str = NULL;
	lines_total = 0;
	fd = ft_open_map_file(file);
	line = ft_get_next_line(fd);
	if (fd == -1 || line == NULL)
		ft_free_map_and_error(map);
	while (line)
	{
		lines_total++;
		tmp_line = ft_strjoin(map_str, line);
		free(line);
		free(map_str);
		line = ft_get_next_line(fd);
		map_str = ft_strdup(tmp_line);
		free(tmp_line);
	}
	map->data = ft_split(map_str, '\n');
	map->h = lines_total;
	free(map_str);
}
