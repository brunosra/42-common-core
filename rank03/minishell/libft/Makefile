NAME = libft.a

FUNC_1 = ft_isalpha.c ft_memcmp.c ft_strlcat.c ft_strncat.c ft_strrchr.c ft_isascii.c ft_memcpy.c ft_strlcpy.c ft_tolower.c ft_atoi.c ft_isdigit.c ft_memmove.c 
FUNC_2 = ft_substr.c ft_strjoin.c get_next_line.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
# Add more files to sources
FUNC_1 += ft_bzero.c ft_isprint.c ft_memset.c ft_strncmp.c ft_isalnum.c ft_memchr.c ft_strchr.c ft_strnstr.c ft_calloc.c
FUNC_1 += ft_strdup.c ft_strlen.c ft_toupper.c ft_strcat.c ft_strncpy.c ft_strcpy.c ft_strcmp.c ft_strndup.c ft_cmp_str_str.c
FUNC_2 += ft_strtrim.c ft_split.c ft_strmapi.c ft_itoa.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strjoin_all.c

# Use same files from sources, but change .c to .o
OBJS = ${FUNC_1:.c=.o} ${FUNC_2:.c=.o}
BONUS_OBJS = $(BONUS:.c=.o)

# @ supress commands terminal
RM = @rm -rf

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g

MK_LIB = ar rcs

all: $(NAME) clean

bonus: $(NAME) $(BONUS_OBJS)
	$(MK_LIB) $(NAME) $(BONUS_OBJS)

#r   Insert the files member... into archive (with replacement). This operation differs from q in that any previously existing members are deleted if their names match those being added.
#s   Add an index to the archive, or update it if it already exists. Note this command is an exception to the rule that there can only be one command letter, as it is possible to use it as either a command or a modifier.  In either case it does the same thing.
#c   Create the archive.  The specified archive is always created if it did not exist, when you request an update.  But a warning is issued unless you specify in advance that you expect to create it, by using this modifier.
$(NAME): $(OBJS)
	$(MK_LIB) $(NAME) $(OBJS)

# clean temporary files: the object files in a C project
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

# clean both object files and the executable
fclean: clean
	$(RM) $(NAME)

# clean and re-compile:
re: fclean
	$(MAKE) all

# phony will run, independent from the state of the file system, avoid make in files with same name
.PHONY: all clean fclean re
