NAME = minishell

HEADER = includes/minishell.h

SRCS = $(wildcard srcs/*.c$)

OBJS = $(subst srcs/,.objs/,$(SRCS:.c=.o))

LIBFT = libft/libft.a

LIB_DEPS = $(wildcard libft/*.c$)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LINK = -L libft -lft

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER) $(LIBFT)
	$(CC) .objs/*.o $(LINK) -o $@

.objs/%.o : srcs/%.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -I includes -c -o $@ $<

$(LIBFT) : $(LIB_DEPS)
	make -C libft

.PHONY : clean fclean re

clean :
	rm -f libft/*\.o$
	rm -f .objs/*\.o$

fclean : clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re : fclean all
