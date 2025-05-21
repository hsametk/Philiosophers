NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = philo.c \
       input_validation_utils.c \
       create_threads.c \
       routine.c \
       utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re