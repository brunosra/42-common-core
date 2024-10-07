###################
#   BASIC SETUP   #
###################

NAME = push_swap
SRCS = src/main.c \
	   src/utils/*.c \
	   src/operations/*.c

###################
#      LIBFT      #
###################
LIBFT = libft.a
DIR_LIBFT = ./libft

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

$(NAME): $(DIR_LIBFT)/$(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(DIR_LIBFT)/$(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(MAKE) clean -C $(DIR_LIBFT)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(DIR_LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
