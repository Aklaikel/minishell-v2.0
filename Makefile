NAME = minishell
INC = include
SRCS = minishell.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
RM =  rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -lreadline -I $(INC) $(SRCS) -o $(OBJS)

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)