/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_not_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:04:48 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:26:09 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_is_map_not_empty(t_map *map)
{
	if (map->data == NULL)
		return (0);
	return (1);
}
