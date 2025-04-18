# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 21:30:59 by menwu             #+#    #+#              #
#    Updated: 2024/11/01 19:23:40 by menwu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
AR = ar rcs
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
HEADER = ft_printf.h

SRC = ft_strlen.c ft_putchar.c ft_putstr.c ft_num_print.c \
      ft_address_print.c ft_hexa_print.c ft_printf.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile $(HEADER)
	$(AR) $(NAME) $(OBJS)

%.o: %.c Makefile $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re	
