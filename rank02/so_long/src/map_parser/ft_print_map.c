/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:16:50 by bschwell          #+#    #+#             */
/*   Updated: 2024/09/15 11:25:02 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_printmap(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i] != NULL)
	{
		ft_printfc(C_CY, "line[%d]: ", i);
		ft_printf("%s\n", map->data[i++]);
	}
}
