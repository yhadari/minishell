NAME = minishell

FT = main.c execute/*.c builtins/*.c get_next_line/*.c libft/*.c

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror -fsanitize=address -g $(FT) -o $(NAME)

clean :
	@rm -rf *.o *.dSYM

fclean : clean
	@rm -f $(NAME)

re : fclean all
