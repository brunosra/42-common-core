/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_won.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:10:44 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 11:40:14 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_check_won(t_game *game, int x, int y)
{
	if (game->map->data[y][x] == 'E' && game->map->n_e == 0)
	{
		ft_print_suc(GAME_COMPLETE);
		ft_free_game_and_exit(game);
	}
}
