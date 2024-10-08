/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:21:27 by bschwell          #+#    #+#             */
/*   Updated: 2024/10/08 11:45:06 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# ifndef SPRITE_SIZE
#  define SPRITE_SIZE 32
# endif

# ifndef BITS_PER_PIXEL
#  define BITS_PER_PIXEL 32
# endif

typedef struct s_map
{
	char	**data;
	int		w;
	int		h;
	int		n_c;
	int		n_e;
	int		n_p;
	int		e_x;
	int		e_y;
	int		p_x;
	int		p_y;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_point	tile_pos;
}	t_image;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*win;
	int		move_count;
	int		fps;
	int		sprite_size;
}	t_game;

/* typedef struct	s_sprites
{
	t_img	map;
	int		fps;
	int		sprite_size;
}				t_game; */

/* Helpers: Outputter Functions */
void	ft_print_err(char *msg);
void	ft_print_wrn(char *msg);
void	ft_print_msg(char *msg);
void	ft_print_suc(char *msg);

/* Reporters */
void	ft_exit_error(char *msg);

/* Map Parser */
int		ft_open_map_file(char *file);
void	ft_create_game_map(char *file, t_map *map);
void	ft_printmap(t_map *map);

/* Map Checker */
int		ft_is_collectible(t_map *map);
int		ft_is_exit(t_map *map);
int		ft_is_start(t_map *map);
int		ft_is_map_not_empty(t_map *map);
int		ft_is_map_surrounded_by_walls(t_map *map);
int		ft_is_map_rect(t_map *map);
int		ft_is_path_valid(t_map *map);
int		ft_is_specials(t_map *map);
int		ft_check_map(t_map *map);

/* Cleaners */
void	ft_free_map(t_map *map);
void	ft_free_map_and_exit(t_map *map);
void	ft_free_game_and_exit(t_game *game);
void	ft_free_game(t_game *game);

/* Render */
void	ft_render(t_game *game);
void	ft_put_tile(t_game *game, char *path, int x, int y);

/* Game Engine */
void	ft_start_game(t_game *game);
int		ft_handle_keypress(int k, t_game *game);
int		ft_handle_destroy(t_game *game);
int		ft_move_right(t_game *game);
int		ft_move_left(t_game *game);
int		ft_move_up(t_game *game);
int		ft_move_down(t_game *game);
void	ft_collect(t_game *game, int x, int y);
void	ft_check_won(t_game *game, int x, int y);
void	ft_update_move_count(t_game *game);
int		ft_check_move(t_game *game, int x, int y);

# define ERROR_READ "Unsuccessfull file read\n"
# define ERROR_RECTANGLE "Map must be a rectangle\n"
# define ERROR_EMPTY_LINE "Map has an empty line\n"
# define ERROR_WALLS "Map must be surrounded by walls\n"
# define ERROR_GAME_INIT "Game initialization failed\n"
# define ERROR_NO_ARG "No arguments"
# define ERROR_COL_ROW "Map has less than 3 rows and/or 3 columns\n"
# define ERROR_EXIT "You must have exactly one exit\n"
# define ERROR_PLAYER "You must have exactly one player\n"
# define ERROR_COLLECT "You need at least one collectable\n"
# define ERROR_CHARS "Map has invalid characters.\
 Allowed characters: 0, 1, P, C, E\n"
# define ERROR_FILE_READ "Can\'t open file.\n"
# define ERROR_PATH "Map does not have a valid path\n"
# define ERROR_IMG_LOAD "Could not load image\n"
# define GAME_COMPLETE "Congratulations! You completed the game!\n"

/* XPM Sprite Files */
# define SPR_0	"./textures/floor.xpm"
# define SPR_1	"./textures/wall.xpm"
# define SPR_P0	"./textures/hero_0.xpm"
# define SPR_P1	"./textures/hero_1.xpm"
# define SPR_E0	"./textures/exit_closed.xpm"
# define SPR_E1	"./textures/exit_open.xpm"
# define SPR_C0	"./textures/key_0.xpm"
# define SPR_C1	"./textures/key_1.xpm"
# define SPR_C2	"./textures/key_2.xpm"
# define SPR_C3	"./textures/key_3.xpm"

/* KeySyms */
# define XK_ESCAPE		0xff1b  // ESC
# define XK_LEFT		0xff51  /* left arrow */
# define XK_UP			0xff52  /* up arrow */
# define XK_RIGHT		0xff53  /* right arrow */
# define XK_DOWN		0xff54  /* down arrow */
# define XK_KP_LEFT		0xff96  /* Keypad left arrow */
# define XK_KP_UP		0xff97  /* Keypad up arrow */
# define XK_KP_RIGHT	0xff98  /* Keypad right arrow */
# define XK_KP_DOWN		0xff99  /* Keypad down arrow */
# define XK_CA			0x0041  /* U+0041 LATIN CAPITAL LETTER A - left */
# define XK_CD			0x0044  /* U+0044 LATIN CAPITAL LETTER D - right */
# define XK_CS			0x0053  /* U+0053 LATIN CAPITAL LETTER S - down */
# define XK_CW			0x0057  /* U+0057 LATIN CAPITAL LETTER W - up */
# define XK_SA			0x0061  /* U+0061 LATIN SMALL LETTER A - left */
# define XK_SD			0x0064  /* U+0064 LATIN SMALL LETTER D - right */
# define XK_SS			0x0073  /* U+0073 LATIN SMALL LETTER S - down */
# define XK_SW			0x0077  /* U+0077 LATIN SMALL LETTER W - up */

#endif
