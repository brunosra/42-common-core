/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_collectible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:09:28 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 11:41:27 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_collectible(t_map *map)
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
			if (map->data[i][j++] == 'C')
				c++;
		}
		i++;
	}
	if (c == 0)
	{
		ft_print_err(ERROR_COLLECT);
		return (0);
	}
	ft_print_suc(ERROR_COLLECT);
	return (1);
}
