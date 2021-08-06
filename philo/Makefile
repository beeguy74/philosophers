CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD #-g -fsanitize=address 
VPATH := include
SRCS = main.c validator.c init.c utils.c

INC = philo.h struct.h

OBJ = $(SRCS:.c=.o)
DEPENDS = ${SRCS:.c=.d}
NAME = philo

.PHONY: all clean fclean re

all: $(SRCS) $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) -o $(NAME)

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -I./include

clean:
		@rm -rf $(OBJ) $(DEPENDS)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

-include ${DEPENDS}
