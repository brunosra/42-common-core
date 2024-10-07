/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_move_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:04:11 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 11:12:23 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_update_move_count(t_game *game)
{
	game->move_count++;
	ft_printf(C_BL"Move Count:"RST"%d\n", game->move_count);
}
