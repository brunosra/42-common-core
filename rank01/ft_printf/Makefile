###################
#   BASIC SETUP   #
###################

NAME = libftprintf.a
SRCS = ft_printf.c ft_putchar.c ft_putstr.c\
		ft_putnbr.c ft_putnbr_base.c ft_putptr.c\

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
CFLAGS = -Wall -Werror -Wextra -c
RM = rm -f

all: $(NAME)

$(DIR_LIBFT)/$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)
	$(MAKE) bonus -C $(DIR_LIBFT)

$(NAME): $(DIR_LIBFT)/$(LIBFT) $(OBJS)
	cp $(DIR_LIBFT)/$(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

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
