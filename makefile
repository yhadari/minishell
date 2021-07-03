NAME = minishell

FT = main.c builtins/*.c get_next_line/*.c libft/*.c

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror $(FT) -o $(NAME)

clean :
	@rm -f *.o

fclean : clean
	@rm -f $(NAME)

re : fclean all
