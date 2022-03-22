SRCS = vector.c

OBJS = $(SRCS:.c=.o)

NAME = libvec.a

CFLAGS		= -g -Wall -Werror -Wextra

CC = clang

RM = rm -f

all: $(NAME)


$(NAME): 	$(OBJS)
	ar rc $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all