/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uss4ma <uss4ma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:59 by osallak           #+#    #+#             */
/*   Updated: 2022/08/13 02:11:05 by uss4ma           ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include "gc.h"
# include "../printf_err/ft_printf.h"
# define CMDLIST 1024

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
	OBRACKET,
	CBRACKET,
	SQUOTE,
	DQUOTE,
	_SPACE,
	WC,
	TILDE,
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
	int		is_runing;
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
typedef struct s_cmdlist
{
	char				*cmd;
	struct s_cmdlist	*next;
}						t_cmdlist;

//the role of the errorflag variable is in case of an error 
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

extern t_global	g_global;

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
int			tokenize_wildcard(t_tokens **head, char *input);
void		tokenize_quotes_helper(t_tokens **head, char *input, int i);
bool		is_not_token(char c);
bool		isword(int c);
bool		isredirect(int flag);
void		set_status(int status);
//Syntax analyser functions
int			isbalanced_brackets(t_tokens *head);
int			isbalanced_quotes(t_tokens *head);
int			syntax_analyser(t_tokens *tokens);
int			check_red_tokens(t_tokens *tokens);
int			check_opar(t_tokens *tokens);
int			check_cpar(t_tokens *tokens);
bool		is_string(int flag);
bool		isredirect(int flag);
void		print_syntax_error(char *error);
void		init_flags(t_pcn_flags *flags, t_tokens *tokens);
int			check_cpar_left(t_tokens *tokens);
int			check_cpar_right(t_tokens *tokens);
int			check_opar_left(t_tokens *tokens);
int			check_opar_right(t_tokens *tokens);
int			check_and_or_pipe_bg(t_tokens *tokens);
int			check_brackets(t_tokens *tokens);
int			get_next_flag(t_tokens *token);
//signals handler functions
void		sigint_handler(int siq);
void		handle_signals(void);
void		sigreset(void);
//env functions
t_env		*add_new_env(char *line);
void		add_back_env(t_env **head, t_env *new);
t_env		*get_env(char **env);
void		remove_quotes(t_tokens **tokens);
void		merge_words(t_tokens **head);
void		remove_spaces(t_tokens **tokens);
void		find_remove_env(char *find, t_env **venv);
char		*find_env(char *find, t_env *venv);
//parser
t_tree		*parser(t_tokens **tokens);
t_tree		*parse_cmdline(t_tokens **tokens);
t_tree		*parse_pipeline(t_tokens **tokens);
t_tree		*parse_command(t_tokens **tokens);
t_tree		*parse_cmdlist(t_tokens **tokens);
int			parse_heredoc(t_tokens **tokens, int *err);
t_cmdlist	*create_cmd_list(char *cmd);
void		add_back_cmdlist(t_cmdlist **head, t_cmdlist *new);
t_tree		*connect_tree(t_tree *left, t_tree *right, t_tokens_flag type);
int			parse_inred(t_tokens **token, int *err);
int			parse_outred(t_tokens **token, int *err);
//expander
void		expander(t_env *env, t_tokens **tokens);
void		add_back(t_env **lst, t_env *new);
//execution utils
int			get_status(int x);
void		handle_red(int *fd);
char		*append_char(char *str, char c);
char		*get_path(char *word, t_env *env);
char		**env_arr(t_env *env);
//execution
void		run(t_tree *cmd, t_env **env);
void		execute_cmd(char *cmd, char **argv, t_env **env, int *fd);
void		run_and_or(t_tree *cmd, t_env **env);
void		pipe_handler(t_tree	*cmd, t_env **env);
void		sigreset(void);
// builting cmds
void		cd_cmd(char **cmd, t_env *env);
void		echo_cmd(char **cmd, int *fd);
void		env_cmd(char **cmd, t_env *venv);
void		exit_cmd(char **cmd);
void		export_cmd(char **cmd, t_env **venv);
void		pwd_cmd(char **cmd, int *fd);
void		unset_cmd(char **cmd, t_env **env);
bool		display_version(char **av, int ac);

#endif