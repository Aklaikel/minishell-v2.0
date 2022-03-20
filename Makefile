NAME = minishell
INC = includes
SRCS = minishell.c \
		g_c/add_front.c \
		g_c/add_new.c \
		g_c/clear_exit.c \
		g_c/collect.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
RM =  rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(LIBFT):
	@make bonus -C libft
$(PRINTF):
	@make -C printf_err
clean :
	$(RM) $(OBJS)
	@make clean -C libft
	@make clean -C printf_err
fclean : clean
	$(RM) $(NAME)
	@make clean -C libft
	@make clean -C printf_err