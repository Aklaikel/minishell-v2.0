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
		SyntaxAnalyser/check_basic_errors.c \
		SyntaxAnalyser/syntax_analyser.c \
		SyntaxAnalyser/check_barckets.c \
		SyntaxAnalyser/syntax_analyser_utils.c \
		SyntaxAnalyser/check_and_or_pipe_bg.c \
		SyntaxAnalyser/set_status.c \
		SyntaxAnalyser/check_brackets_utils.c \
		expander/expander.c \
		expander/get_env.c \
		expander/get_env_utils.c \
		expander/remove_unwanted_tokens.c \


OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
RM =  rm -rf

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(PRINTF)
		$(CC) $(CFLAGS) -lreadline -lncurses $^ -o $(NAME) -L /goinfre/osallak/.brew/opt/readline/lib 

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ -I /goinfre/osallak/.brew/opt/readline/include

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
