/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:10:44 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 12:06:09 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_move(t_game *game, int x, int y)
{
	char	c;

	if (x >= game->map->w || y >= game->map->h)
		return (0);
	c = game->map->data[y][x];
	if (c == '1')
		return (0);
	return (1);
}
