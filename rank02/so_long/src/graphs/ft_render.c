/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:11:20 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/04 10:50:12 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_render(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map->w)
	{
		y = 0;
		while (y < game->map->h)
		{
			if (game->map->data[y][x] == '0')
				ft_put_tile(game, SPR_0, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			else if (game->map->data[y][x] == '1')
				ft_put_tile(game, SPR_1, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			else if (game->map->data[y][x] == 'C')
				ft_put_tile(game, SPR_C0, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			else if (game->map->data[y][x] == 'E' && game->map->n_e == 1)
				ft_put_tile(game, SPR_E0, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			else if (game->map->data[y][x] == 'E' && game->map->n_e == 0)
				ft_put_tile(game, SPR_E1, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			else if (game->map->data[y][x] == 'P')
				ft_put_tile(game, SPR_P0, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
			y++;
		}
		x++;
	}
}
