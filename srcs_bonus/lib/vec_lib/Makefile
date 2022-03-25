SRCS = vector.c vec_basic.c vec_matrix.c

OBJS = $(SRCS:.c=.o)

NAME = libvec.a

CFLAGS = -g -Wall -Werror -Wextra

CC = gcc

RM = rm -f

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -n "\033[1;32m█\033[0m"

$(NAME): 	$(OBJS)
	@ar rc $(NAME) $(OBJS)


clean:
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re: fclean all