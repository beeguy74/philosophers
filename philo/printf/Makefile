# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tphung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 18:37:57 by tphung            #+#    #+#              #
#    Updated: 2021/07/25 15:59:05 by tphung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD
VPATH := includes:libft

SRCS = ft_printf.c ft_parser.c ft_str_ch.c ft_numb_procs.c \
		ft_numb_utils.c ft_pointer.c ft_print_utils.c
INC = ft_printf.h libft.h
OBJ = $(SRCS:.c=.o)
NAME = libftprintf.a
DEPENDS = ${SRCS:.c=.d}
LIBFT = libft.a
LIBFT_DIR = libft/

.PHONY: all clean fclean re

all: lib $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

lib:
		make -C $(LIBFT_DIR)
		cp $(LIBFT_DIR)$(LIBFT) ./$(NAME)

.c.o: $(SRCS)
		$(CC) $(FLAGS)  -c $< -o $@ -I./includes -I./libft

clean:
		rm -rf $(OBJ) $(DEPENDS)
		make clean -C $(LIBFT_DIR)

fclean: clean
		rm -rf $(NAME) $(LIBFT)
		make fclean -C $(LIBFT_DIR)

re: fclean all
