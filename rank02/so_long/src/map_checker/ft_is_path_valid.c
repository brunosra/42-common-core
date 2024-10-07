/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_path_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:39:14 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 15:21:17 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_map	*ft_dup_map(t_map *map)
{
	int		tmp_h;
	t_map	*tmp_map;

	tmp_map = ft_calloc(1, sizeof(t_map));
	tmp_h = 0;
	tmp_map->data = ft_calloc(map->h + 1, sizeof(char *));
	while (tmp_h < map->h)
	{
		tmp_map->data[tmp_h] = ft_strdup(map->data[tmp_h]);
		tmp_h++;
	}
	tmp_map->n_c = map->n_c;
	tmp_map->n_e = map->n_e;
	tmp_map->n_p = map->n_p;
	tmp_map->w = map->w;
	tmp_map->h = map->h;
	return (tmp_map);
}

int	ft_flood_fill(int x, int y, t_map *tmp_map)
{
	if (x < 0 || y < 0 || x >= tmp_map->h || y >= tmp_map->w)
		return (0);
	if (tmp_map->data[x][y] == 'E')
		tmp_map->n_e--;
	if (tmp_map->n_c == 0 && tmp_map->n_e == 0)
		return (1);
	if (tmp_map->data[x][y] == '1')
		return (0);
	if (tmp_map->data[x][y] == 'C' && tmp_map->n_c > 0)
		tmp_map->n_c--;
	tmp_map->data[x][y] = '1';
	if (ft_flood_fill(x - 1, y, tmp_map) || ft_flood_fill(x + 1, y, tmp_map)
		|| ft_flood_fill(x, y - 1, tmp_map) || ft_flood_fill(x, y + 1, tmp_map))
		return (1);
	return (0);
}

int	ft_is_path_valid(t_map *map)
{
	t_map	*tmp_map;
	int		result;

	tmp_map = ft_dup_map(map);
	result = ft_flood_fill(map->p_x, map->p_y, tmp_map);
	ft_free_map(tmp_map);
	return (result);
}
