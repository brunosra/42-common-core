/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_surrounded_by_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:06:26 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:28:54 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_map_surrounded_by_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (i == 0 || i == (map->h - 1))
			{
				if (map->data[i][j] != '1')
					return (0);
			}
			else
			{
				if ((j == 0 || j == (map->w - 1)) && map->data[i][j] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
