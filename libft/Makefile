# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 15:40:30 by menwu             #+#    #+#              #
#    Updated: 2025/06/24 19:31:05 by gapujol-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcs
NAME = libft.a
SRC = ft_isalpha.c ft_isdigit.c ft_tolower.c ft_isalnum.c ft_isascii.c \
ft_strchr.c ft_isprint.c ft_strrchr.c ft_toupper.c ft_calloc.c ft_strcmp.c ft_strdup.c \
ft_strlen.c ft_strncmp.c ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c \
ft_memmove.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJS) Makefile $(HEADER)
	 $(AR) $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(OBJS_BONUS) Makefile $(HEADER)
	$(AR) $(NAME) $(OBJS_BONUS)
	touch .bonus
	
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all bonus

.PHONY: all clean fclean re bonus
