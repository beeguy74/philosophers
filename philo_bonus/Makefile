CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD -pthread#-g -fsanitize=address
VPATH := include
SRCS = main.c validator.c utils.c init.c init_forks.c

INC = philo.h struct.h

OBJ = $(SRCS:.c=.o)
DEPENDS = ${SRCS:.c=.d}
NAME = philo_bonus

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
