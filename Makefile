NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address #quitar debugger 

RM = rm -rf

LIBFT = libft/libft.a

SRCS = 	src/pipex.c\
		src/pipex_utils.c\

OBJ =  $(SRCS:.c=.o)

CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(NAME) : $(OBJ)
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	make all -C libft
	gcc $(CFLAGS)  $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(NAME)
	$(RM) $(OBJ)
	make clean -C libft

re : fclean all

.PHONY:     all clean fclean re bonus
