/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:59:11 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 15:52:29 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_handle_keypress(int k, t_game *game)
{
	if (k == XK_ESCAPE)
		ft_free_game_and_exit(game);
	if (k == XK_RIGHT || k == XK_KP_RIGHT || k == XK_CD || k == XK_SD)
		ft_move_right(game);
	if (k == XK_LEFT || k == XK_KP_LEFT || k == XK_CA || k == XK_SA)
		ft_move_left(game);
	if (k == XK_UP || k == XK_KP_UP || k == XK_CW || k == XK_SW)
		ft_move_up(game);
	if (k == XK_DOWN || k == XK_KP_DOWN || k == XK_CS || k == XK_SS)
		ft_move_down(game);
	return (0);
}
