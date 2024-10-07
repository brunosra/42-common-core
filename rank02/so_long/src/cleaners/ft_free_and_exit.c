/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:17:42 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 16:00:21 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_free_map_and_exit(t_map *map)
{
	free(map);
	exit(EXIT_FAILURE);
}

void	ft_free_game_and_exit(t_game *game)
{
	ft_free_game(game);
	exit(EXIT_FAILURE);
}

void	ft_free_game(t_game *game)
{
	if (game)
	{
		if (game->map)
			ft_free_map(game->map);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
}
