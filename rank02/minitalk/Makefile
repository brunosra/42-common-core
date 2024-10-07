###################
#   BASIC SETUP   #
###################

NAME_SERVER = server
NAME_CLIENT = client
SRC_SERVER = src/server.c
SRC_CLIENT = src/client.c

###################
#   BONUS SETUP   #
###################

NAME_SERVER_B = server_bonus
NAME_CLIENT_B = client_bonus
SRC_SERVER_B = src_bonus/server_bonus.c
SRC_CLIENT_B = src_bonus/client_bonus.c

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

all: $(NAME_SERVER) $(NAME_CLIENT)

$(DIR_LIBFT)/$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)
	$(MAKE) bonus -C $(DIR_LIBFT)

$(NAME_SERVER): $(DIR_LIBFT)/$(LIBFT) $(SRC_SERVER)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(DIR_LIBFT)/$(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(DIR_LIBFT)/$(LIBFT) $(SRC_CLIENT)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(DIR_LIBFT)/$(LIBFT) -o $(NAME_CLIENT)

bonus: $(NAME_SERVER_B) $(NAME_CLIENT_B)

$(NAME_SERVER_B): $(DIR_LIBFT)/$(LIBFT) $(SRC_SERVER_B)
	$(CC) $(CFLAGS) $(SRC_SERVER_B) $(DIR_LIBFT)/$(LIBFT) -o $(NAME_SERVER_B)

$(NAME_CLIENT_B): $(DIR_LIBFT)/$(LIBFT) $(SRC_CLIENT_B)
	$(CC) $(CFLAGS) $(SRC_CLIENT_B) $(DIR_LIBFT)/$(LIBFT) -o $(NAME_CLIENT_B)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(MAKE) clean -C $(DIR_LIBFT)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(DIR_LIBFT)
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_B) $(NAME_CLIENT_B)

re:	fclean all

.PHONY: all clean fclean re bonus