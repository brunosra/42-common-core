/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:10:39 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/25 16:21:17 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_map(t_map *map)
{
	if (ft_is_map_not_empty(map) == 0)
		return (0);
	else if (ft_is_map_rect(map) == 0)
		return (0);
	else if (ft_is_map_surrounded_by_walls(map) == 0)
		return (0);
	else if (ft_is_exit(map) == 0)
		return (0);
	else if (ft_is_start(map) == 0)
		return (0);
	else if (ft_is_specials(map) == 0)
		return (0);
	else if (ft_is_path_valid(map) == 0)
		return (0);
	return (1);
}
