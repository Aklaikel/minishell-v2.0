/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:59 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 05:05:45 by aklaikel         ###   ########.fr       */
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
# include <errno.h>
# include "gc.h"
# include "../printf_err/ft_printf.h"
#define CMDLIST 1024

#ifdef NULL
#undef NULL
#define NULL (void *)0x0
#endif

typedef enum tokens
{
	WORD,
	VAR,
	OUTRED,
	INRED,
	APPEND,
	HERDOC,
	PIPE,
	AND,
	OR,
	BG,
	OBRACKET,
	CBRACKET,
	SQUOTE,
	DQUOTE,
	_SPACE,
}	t_tokens_flag;

typedef struct s_tokens
{
	char			*token;
	int				flag;
	struct s_tokens	*next;
	struct s_tokens	*previous;
}	t_tokens;

//pcn stands for previous, current and next
typedef struct s_pcn_flags
{
	int				prev;
	int				curr;
	int				next;
}	t_pcn_flags;

//the struct below should be global and also contains
//the exit status for the last command and maybe a variable named is running
typedef struct s_global
{
	t_gc	*g_garbage;
	int		exit_status;
}	t_global;

//the next struct contains all env variables and  it's values
typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	struct s_env	*next;
}	t_env;

//the struct below contains the input/output file descriptors for every cmd 
// the default value is 0 for in and 1 for out

struct s_io
{
	int	infd;
	int	outfd;
};

//the folowing struct contains the cmd/arg
typedef struct	s_cmdlist
{
	char				*cmd;
	struct s_cmdlist	*next;
}						t_cmdlist;

//the role of the errorflag variable is inn case of an error 
//in the opening/creating of the in/outfiles it will contains the errno
typedef struct s_tree
{
	int				type;
	t_cmdlist		*cmdlist;
	int				infd;
	int				outfd;
	int				errorflag;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


extern t_global g_global;

// double linked list
t_tokens	*node_del_dll(t_tokens **dll, t_tokens *node);
void		del_dll(t_tokens **dll);
t_tokens	*init_list_dll(char *input, int flag);
void		add_back_dll(t_tokens **tokens_list, t_tokens *new);

//tokenizer functions
t_tokens	*init_list_dll(char *input, int flag);
void		add_back_dll(t_tokens **tokens_list, t_tokens *new);
t_tokens	*tokenizer(char *input);
int			get_tokens(t_tokens **head, char *input, int len, int flag);
int			tokenize_word(t_tokens **head, char *input, int flag);
int			tokenize_space(t_tokens **head, char *input);
int			tokenize_quotes(t_tokens **head, char *input);
int			tokenize_variables(t_tokens **head, char *input);
bool		isword(int c);
void		set_status(int status);
//Syntax analyser functions
void		isbalanced_brackets(t_tokens *head);
void		isbalanced_quotes(t_tokens *head);
void		syntax_analyser(t_tokens *tokens);
void		check_red_tokens(t_tokens *tokens);
void		check_opar(t_tokens *tokens);
void		check_cpar(t_tokens *tokens);
bool		is_string(int flag);
bool		isredirect(int flag);
void		print_syntax_error(char *error);
void		init_flags(t_pcn_flags *flags, t_tokens *tokens);
void		check_cpar_left(t_tokens *tokens);
void		check_cpar_right(t_tokens *tokens);
void		check_opar_left(t_tokens *tokens);
void		check_opar_right(t_tokens *tokens);
void		check_and_or_pipe_bg(t_tokens *tokens);
void		check_brackets(t_tokens *tokens);
int			get_next_flag(t_tokens *token);
/*****************  expander functions  ********************/
//env functions
t_env		*add_new_env(char *line);
void		add_back_env(t_env **head, t_env *new);
t_env		*get_env(char **env);
void		remove_quotes(t_tokens **tokens);
void		merge_words(t_tokens **head);
void		remove_spaces(t_tokens **tokens);
void		display(t_tokens *tokens);
void		find_remove_env(char *find, t_env **venv);
char		*find_env(char *find, t_env *venv);
//parser
t_tree		*parser(t_tokens **tokens);
t_tree  	*parse_cmdline(t_tokens **tokens);
t_tree		*parse_pipeline(t_tokens **tokens);
t_tree		*parse_command(t_tokens **tokens);
t_tree		*parse_cmdlist(t_tokens **tokens);
//expander
//char	*get_var_value(t_env *env, char *varname);
//void	expander(t_env *env, t_tokens *tokens);

//execution
void    run(t_tree  *cmd, char **env);
void	execute_cmd(char *cmd, char **argv, char **env);
// builting cmds
void	cd_cmd(char **cmd, t_env *env);
void	echo_cmd(char **cmd);
void	env_cmd(char **cmd, t_env *venv);
void	exit_cmd(char **cmd);
void	export_cmd(char **cmd, t_env **venv);
void	pwd_cmd(char **cmd);
void	unset_cmd(char **cmd, t_env **env);

#endif