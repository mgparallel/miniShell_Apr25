CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -Llibft -lreadline -lncurses
INCLUDES = -I$(LIBFT_DIR) -I/opt/homebrew/opt/readline/include
LIBFT_DIR = libft
LIBFT = libft/libft.a
HEADER = minishell.h
RM = rm -rf
NAME = minishell

SRCS = 0_copy_env.c 0_add_node_to_lst.c 0_create_token.c \
0_tokenize_input.c 0_tokenizer.c 0_tokenizer_util.c 1_get_var_value.c \
1_if_cmd.c 1_if_exit_code.c 1_lst_remove_token.c 1_parse_arg.c 1_parse_quote.c \
1_parse_quote_util.c 1_parse_var.c 1_parse_word.c 1_parsing.c 1_update_token.c \
2_clear_token.c 2_expand_var_heredoc.c 2_handle_sigint.c 2_update_var_value.c \
build_cmd_utils.c build_commands.c command.c exec_builtins.c exec_commands.c \
exec_utils.c expand_exit_code.c expand_exit_status.c heredoc.c main.c \
redirections.c 03_builtin/builtin_util.c 03_builtin/cmd_cd.c 03_builtin/cmd_echo.c \
03_builtin/cmd_exit.c 03_builtin/cmd_export.c 03_builtin/cmd_export_extra.c \
03_builtin/cmd_pwd_env.c 03_builtin/cmd_unset.c 03_builtin/declare_export.c \
04_bonus_wildcard/expand_wildcard.c 04_bonus_wildcard/fn_match.c \
04_bonus_wildcard/free_arr.c 04_bonus_wildcard/if_wildcard.c 04_bonus_wildcard/init_fn_lst.c \
04_bonus_wildcard/manipulate_arr.c 04_bonus_wildcard/strmatch.c 04_bonus_wildcard/wildcard_util.c

LIBFT_SRC = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_tolower.c libft/ft_isalnum.c libft/ft_isascii.c \
libft/ft_strchr.c libft/ft_isprint.c libft/ft_strrchr.c libft/ft_toupper.c libft/ft_calloc.c libft/ft_strcmp.c libft/ft_strdup.c \
libft/ft_strlen.c libft/ft_strncmp.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memchr.c libft/ft_memcpy.c libft/ft_memcmp.c \
libft/ft_memmove.c libft/ft_strnstr.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_atoi.c libft/ft_substr.c libft/ft_strjoin.c \
libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) -fsanitize=address

%.o: %.c $(HEADER)
	@echo "compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFT_SRC) libft/libft.h
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libft
