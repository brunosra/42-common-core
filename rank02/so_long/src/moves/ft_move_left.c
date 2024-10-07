/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:09:05 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 14:12:01 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_move_left(t_game *game)
{
	int	res;
	int	p_x;
	int	p_y;

	p_x = game->map->p_x;
	p_y = game->map->p_y;
	res = ft_check_move(game, p_x - 1, p_y);
	if (res == 1)
	{
		ft_update_move_count(game);
		ft_collect(game, p_x - 1, p_y);
		game->map->p_x--;
		game->map->data[p_y][p_x - 1] = 'P';
		if (p_y == game->map->e_y && p_x == game->map->e_x)
			game->map->data[p_y][p_x] = 'E';
		else
			game->map->data[p_y][p_x] = '0';
	}
	ft_render(game);
	return (0);
}
