# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osallak <osallak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 01:55:25 by aklaikel          #+#    #+#              #
#    Updated: 2022/06/03 09:19:41 by osallak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a
SRCS =  ft_printf.c\
		ft_print_HEXAA.c\
		ft_print_hexa.c\
		ft_printstr.c\
		ft_putchar_fd.c\
		ft_putnbr_fd.c\
		ft_putnbr_u_fd.c\
		ft_putstr_fd.c\
		length.c
OBJS = $(SRCS:%.c=%.o)

CC = cc
RM = rm -rf
AR = ar -rcs

all = $(NAME)

$(NAME):$(OBJS)
		$(AR) $(NAME) $(OBJS)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@
clean:
		$(RM) $(OBJS)

fclean:
		$(RM) $(NAME) 

re: fclean all
		
