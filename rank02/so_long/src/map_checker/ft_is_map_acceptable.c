/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_acceptable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:08:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/11 08:37:08 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_map_acceptable(t_map *map)
{
	int	i;
	int	j;
	// int	c;

	i = -1;
	// c = 0;
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->w)
			if (map->data[i][j] != '1' && map->data[i][j] != '0' &&
				map->data[i][j] != 'P' && map->data[i][j] != 'E' &&
				map->data[i][j] != 'C')
					return (0);
	}		
	return (1);
}
