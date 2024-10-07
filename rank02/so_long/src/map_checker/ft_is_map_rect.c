/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_rect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:03:15 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:30:03 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_map_rect(t_map *map)
{
	int		i;
	size_t	curr_len;

	i = 0;
	curr_len = ft_strlen(map->data[i]);
	while (map->data[i] != NULL)
	{
		if (curr_len != ft_strlen(map->data[i]))
			return (0);
		if (ft_strlen(map->data[i]) == 0)
			return (0);
		i++;
	}
	map->w = curr_len;
	return (1);
}
