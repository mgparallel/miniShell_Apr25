CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# LDFLAGS use for MacOS
LDFLAGS = -Llibft -L/opt/homebrew/opt/readline/lib -lreadline -lncurses
# LDFLAGS use for Linux
# LDFLAGS = -Llibft -lreadline
INCLUDES = -Ilibft -I/opt/homebrew/opt/readline/include #last argument for MacOS
LIBS = libft/libft.a
HEADER = minishell.h
RM = rm -rf
NAME = minishell

SRCS = $(wildcard *.c) $(wildcard 04_bonus_wildcard/*.c) $(wildcard 03_builtin/*.c)

#LIBFT_SRC = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_tolower.c libft/ft_isalnum.c libft/ft_isascii.c \
libft/ft_strchr.c libft/ft_isprint.c libft/ft_strrchr.c libft/ft_toupper.c libft/ft_calloc.c libft/ft_strcmp.c libft/ft_strdup.c \
libft/ft_strlen.c libft/ft_strncmp.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memchr.c libft/ft_memcpy.c libft/ft_memcmp.c \
libft/ft_memmove.c libft/ft_strnstr.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_atoi.c libft/ft_substr.c libft/ft_strjoin.c \
libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/get_next_line.c

#LIBFT_HEADER = libft/libft.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME) -fsanitize=address

%.o: %.c libft/libft.a libft/libft.h
	@echo "compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a: #$(LIBFT_SRC) $(LIBFT_HEADER)
	$(MAKE) -C libft

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
