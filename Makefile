NAME = minishell
INC = includes
SRCS = minishell.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
RM =  rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) -l readline $(OBJS) -o $(NAME)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $(SRCS) -o $(OBJS)

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)