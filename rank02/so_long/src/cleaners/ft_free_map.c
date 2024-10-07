/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:08 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:12:54 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->data != NULL)
		while (map->data[i] != NULL)
			free(map->data[i++]);
	free(map->data);
	free(map);
}
