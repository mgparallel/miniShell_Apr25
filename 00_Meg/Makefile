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

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME) -fsanitize=address

%.o: %.c
	@echo "compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	$(MAKE) -C libft

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re