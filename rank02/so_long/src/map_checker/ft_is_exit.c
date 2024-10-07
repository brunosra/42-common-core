/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:07:13 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 12:05:08 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_exit(t_map *map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->data[i][j++] == 'E')
			{
				map->e_x = j - 1;
				map->e_y = i;
				c++;
			}
		}
		i++;
	}
	if (c != 1)
		return (0);
	return (1);
}
