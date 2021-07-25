CC = gcc
FLAGS = -Wall -Wextra -MMD #-Werror -g
VPATH := include:printf:printf/libft:printf/includes
SRCS = main.c

INC = philo.h struct.h ft_printf.h libft.h

OBJ = $(SRCS:.c=.o)
DEPENDS = ${SRCS:.c=.d}
LFT = libftprintf.a
NAME = philo

.PHONY: all clean fclean re lib

all: lib $(SRCS) $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) $(LFT) -o $(NAME)

lib :
		make -C printf
		mv printf/$(LFT) .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -I./include -I./printf/includes -I./printf/libft

clean:
		make clean -C ./printf/
		@rm -rf $(LFT)
		@rm -rf $(OBJ) $(DEPENDS)

fclean: clean
		make fclean -C ./printf/
		@rm -rf $(NAME)

re: fclean all

-include ${DEPENDS}
