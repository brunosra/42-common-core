/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:10:44 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:12:13 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_collect(t_game *game, int x, int y)
{
	if (game->map->data[y][x] == 'C')
		game->map->n_c--;
	if (game->map->n_c == 0)
		game->map->n_e = 0;
	ft_check_won(game, x, y);
}
