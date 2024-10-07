/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:55:45 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:25:00 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_start_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map->w * SPRITE_SIZE,
			game->map->h * SPRITE_SIZE, "so_long");
	game->move_count = 0;
	ft_render(game);
	mlx_hook(game->win, 17, 0L, ft_handle_destroy, game);
	mlx_hook(game->win, 2, 1L << 0, ft_handle_keypress, game);
	mlx_loop(game->mlx);
}
