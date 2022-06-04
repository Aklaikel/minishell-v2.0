/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 07:34:48 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 08:12:32 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_heredoc(t_tokens **tokens)
{
	int		fd[2];
	char	*delim;
	char	*input;

	*tokens = (*tokens)->next;
	delim = (*tokens)->token;
	// *tokens = (*tokens)->next;
	if (pipe(fd) == -1)
	{
		perror(NULL);
		clear_exit();
	}
	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			ft_printf("warning: unexpected EOF (wanted `%s')\n", delim);
			close(fd[1]);
			return (-1);
		}
		if (!strcmp(input, delim))
			break ;
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}

t_cmdlist	*create_cmd_list(char *cmd)
{
	t_cmdlist	*new;

	new = (t_cmdlist *)collect(malloc(sizeof(t_cmdlist)));
	new->cmd  = cmd;
	new->next = NULL;
	return (new);
}

void	add_back_cmdlist(t_cmdlist **head, t_cmdlist *new)
{
	t_cmdlist	*node;

	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node && node->next)
		node = node->next;
	node->next = new;
}

t_tree	*connect_tree(t_tree *left, t_tree *right, t_tokens_flag type)
{
	t_tree	*tree;

	tree = (t_tree *)collect(malloc(sizeof(t_tree)));
	tree->left = left;
	tree->right = right;
	tree->type = type;
	tree->errorflag = 0;
	tree->infd = STDOUT_FILENO;
	tree->outfd = STDIN_FILENO;
	tree->cmdlist = NULL;
	return (tree);
}


int	parse_inred(t_tokens **token, int *err)
{
	int	fd;

	*token = (*token)->next;
	fd = open((*token)->token, O_RDONLY);
	if (fd == -1)
	{
		*err = errno;
		return (-1);
	}
	return (fd);
}

int	parse_outred(t_tokens **token, int *err)
{
	int	fd;
	int	flags;

	if ((*token)->flag == APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	*token = (*token)->next;
	fd = open((*token)->token, flags);
	if (fd == -1)
	{
		*err = errno;
		return (-1);
	}
	return (fd);
}

t_tree	*parse_cmdlist(t_tokens **tokens)
{
	t_tree		*tree;
	t_cmdlist	*cmdlist;
	struct s_io io;
	int			err;
	int			visited;

	io.infd = STDIN_FILENO;
	io.outfd = STDOUT_FILENO;
	cmdlist = NULL;
	tree = (t_tree *)collect(malloc(sizeof(t_tree)));
	visited = 0;
	err = 0;
	while (*tokens && (*tokens)->flag != PIPE
		&& (*tokens)->flag != CBRACKET && (*tokens)->flag != AND && (*tokens)->flag != OR && (*tokens)->flag != OBRACKET)
	{
		visited = 1;
		if ((*tokens)->flag == INRED)
		{
			if (io.infd != STDIN_FILENO)
				close(io.infd);
			io.infd = parse_inred(tokens, &err);
		}
		else if ((*tokens)->flag == APPEND || (*tokens)->flag == OUTRED)
		{
			if (io.outfd != STDOUT_FILENO)
				close(io.outfd);
			io.outfd = parse_outred(tokens, &err);	
		}
		else if ((*tokens)->flag == HERDOC)
			io.infd = parse_heredoc(tokens);
		else
			add_back_cmdlist(&cmdlist, create_cmd_list((*tokens)->token));
		if (err != 0)
			break ;
		*tokens = (*tokens)->next;
	}
	if (visited == 0)
		return (NULL);
	tree->errorflag = err;
	tree->cmdlist = cmdlist;
	tree->left = NULL;
	tree->right = NULL;
	tree->type = CMDLIST;
	tree->infd = io.infd;
	tree->outfd = io.outfd;
	return (tree);
}

t_tree  *parse_command(t_tokens **tokens)
{
	t_tree  *tree;

	tree = parse_cmdlist(tokens);
	if (!tree && (*tokens)->flag == OBRACKET)
	{
		*tokens  = (*tokens)->next;
		tree  = parse_cmdline(tokens);
		if (!tree)
			return (NULL);
		if (*tokens && (*tokens)->flag == CBRACKET)
			*tokens = (*tokens)->next;
	}
	return (tree);
}

t_tree  *parse_pipeline(t_tokens **tokens)
{
	t_tree  *tree;
	t_tree	*tmp;

	tree = parse_command(tokens);
	if (!tree)
		return (NULL);
	while (*tokens && (*tokens)->flag == PIPE)
	{
		*tokens = (*tokens)->next;
		tmp = parse_command(tokens);
		if (!tmp)
			return NULL;
		tree  = connect_tree(tree,tmp, PIPE);
	}
	return (tree);
}

t_tree  *parse_cmdline(t_tokens **tokens)
{
	t_tree  *tree;
	t_tree  *tmp;
	int		type;

	tree  = NULL;
	tree  = parse_pipeline(tokens);
	if (!tree)
		return (NULL);
	while (*tokens && ((*tokens)->flag == AND || (*tokens)->flag == OR))
	{
		type = (*tokens)->flag;
		*tokens = (*tokens)->next;
		tmp = parse_pipeline(tokens);
		if (!tmp)
			return (NULL);
		tree = connect_tree(tree , tmp, type);
	}
	return (tree);
}

t_tree	*parser(t_tokens **tokens)
{
	t_tree	*tree;

	tree = NULL;
	if (!tokens || !*tokens)
		return (NULL);
	tree = parse_cmdline(tokens);
	return (tree);
}
