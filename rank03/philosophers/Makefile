###################
#   BASIC SETUP   #
###################

NAME = 	so_long
SRCS = 	src/so_long.c\
		src/**/*.c

LIBS = 	./libs

###################
#      LIBFT      #
###################
LIBFT = libft.a
DIR_LIBFT = $(LIBS)/libft

###################
#    MINILIB-X    #
###################
MLX = libmlx.a
DIR_MLX = $(LIBS)/minilibx-linux
MLXFLAGS = -L $(DIR_MLX) -lmlx -lXext -lX11

###################
#   COMMON CONF   #
###################
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

all: $(NAME)

$(DIR_LIBFT)/$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)
	$(MAKE) bonus -C $(DIR_LIBFT)

$(DIR_MLX)/$(MLX):
	$(MAKE) -C $(DIR_MLX)

$(NAME): $(DIR_LIBFT)/$(LIBFT) $(DIR_MLX)/$(MLX) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(DIR_LIBFT)/$(LIBFT) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(MAKE) clean -C $(DIR_LIBFT)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(DIR_LIBFT)
	$(RM) $(NAME)

norm: 
	norminette libs/libft src

re:	fclean all

.PHONY: all clean fclean re
