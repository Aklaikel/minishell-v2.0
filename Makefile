NAME = minishell

LIBFT = libft/libft.a
PRINTF = printf_err/libftprintf.a

INC = includes
LIBFT = libft/libft.a 
PRINTF = printf_err/libftprintf.a
SRCS = minishell.c \
		g_c/add_front.c \
		g_c/add_new.c \
		g_c/clear_exit.c \
		g_c/collect.c \
		tokenizer/get_tokens.c \
		tokenizer/tokenizer_utils.c \
		tokenizer/tokenizer.c \
		parsing/check_basic_errors.c


OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
RM =  rm -rf

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(PRINTF)
		$(CC) $(CFLAGS) -lreadline -lncurses $^ -o $(NAME)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(LIBFT):
	make bonus -C libft
$(PRINTF):
	make -C printf_err
clean :
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C printf_err
fclean : clean
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C printf_err
re : fclean all
