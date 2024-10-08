/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:09:23 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 11:43:55 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_put_tile(t_game *game, char *path, int x, int y)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path,
			&game->sprite_size, &game->sprite_size);
	if (img == NULL)
	{
		ft_print_err(ERROR_IMG_LOAD);
		ft_free_game_and_exit(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	mlx_destroy_image(game->mlx, img);
}
