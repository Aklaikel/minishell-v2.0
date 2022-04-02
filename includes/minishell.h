/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:59 by osallak           #+#    #+#             */
/*   Updated: 2022/04/01 22:50:36 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include "gc.h"

typedef enum tokens
{
	WORD,
	PIPE,
	OUTRED,
	INRED,
	APPEND,
	HERDOC,
	AND,
	OR,
	SPACE,
	OBRACKET,
	CBRACKET,
	SQUOTE,
	DQUOTE,
	BG,
}	t_tokens_flag;

typedef struct s_tokens
{
	char			*token;
	int				flag;
	struct s_tokens	*next;
	struct s_tokens	*previous;
}	t_tokens;

extern t_gc	*g_garbage;

//tokenizer functions
t_tokens	*init_list_dll(char *input, int flag);
void		add_back_dll(t_tokens **tokens_list, t_tokens *new);
t_tokens	*tokenizer(char *input);
int			get_tokens(t_tokens **head, char *input, int len, int flag);
int			tokenize_word(t_tokens **head, char *input, int flag);
int			tokenize_space(t_tokens **head, char *input);
#endif