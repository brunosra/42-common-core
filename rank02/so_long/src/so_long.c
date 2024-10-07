/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:27:23 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/07 15:14:58 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc == 2)
	{
		if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
			ft_exit_error("Map file must end with .ber!");
		map = (t_map *) ft_calloc(1, sizeof(t_map));
		ft_create_game_map(argv[1], map);
		if (ft_check_map(map) == 0)
		{
			ft_free_map(map);
			ft_exit_error("Map has errors!");
		}
		else
		{
			game = (t_game *) ft_calloc(1, sizeof(t_game));
			game->map = map;
			game->sprite_size = SPRITE_SIZE;
			ft_start_game(game);
		}
	}
	else
		ft_exit_error("Usage: ./so_long "C_CY"[file_path_map]"RST);
	return (0);
}
