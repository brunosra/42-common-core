/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:09:28 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:30:17 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_specials(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->data[i][j] == 'C')
				map->n_c++;
			if (map->data[i][j] == 'P')
			{
				map->p_x = j;
				map->p_y = i;
				map->n_p++;
			}
			if (map->data[i][j++] == 'E')
				map->n_e++;
		}
		i++;
	}
	if (map->n_c == 0 || map->n_e != 1 || map->n_p != 1)
		return (0);
	return (1);
}
