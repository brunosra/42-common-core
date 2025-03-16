# Nome do executável
NAME = minishell

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft

# Nome da biblioteca
LIBFT = $(LIBFT_DIR)/libft.a

# Compilador e flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I $(INC_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L. -lreadline
VALGRIND = valgrind --quiet --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
# Buscar todos os arquivos .c dentro de src e seus subdiretórios
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

# Regra principal
all: $(LIBFT) $(NAME)

# Criação do executável principal
$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Compilação da biblioteca libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(NAME)
	clear && cd ./tester && ./tester	

# Valgrind para rodar o programa e suprimir vazamentos
valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

# Limpeza de arquivos objetos
clean:
	$(MAKE) -C $(LIBFT_DIR) clean

# Limpeza total (inclui biblioteca e executável)
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Recompilar tudo
re: fclean all

# Declarando que não são arquivos reais
.PHONY: all clean fclean  re test valgrind
