NAME = philo
SRC = $(wildcard src/*.c)

RM = @rm -rf
CC = @cc -g -pthread -Wextra -Werror -Wall 

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
