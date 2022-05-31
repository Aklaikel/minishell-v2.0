/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 07:34:48 by osallak           #+#    #+#             */
/*   Updated: 2022/05/31 19:12:01 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_tree	*create_tree(t_tree *left, t_tree *right, t_tokens *token, int par_flag, struct s_io io)
{
	t_tree	*tree;

	tree = (t_tree *)collect(malloc(sizeof(t_tree)));
	tree->left = left;
	tree->right = right;
	tree->par_flag = par_flag;
	tree->type = token->flag;
	tree->infd = io.infd;
	tree->outfd = io.outfd;
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
t_tree	*parse_redirections(t_tokens **tokens)
{
	t_tree		*tree;
	t_cmdlist	*cmdlist;
	struct s_io io;
	int			err;

	io.infd = 0;
	io.outfd = 1;
	cmdlist = NULL;
	tree = (t_tree *)collect(malloc(sizeof(t_tree)));
	err = 0;
	while (*tokens && (*tokens)->flag != PIPE
		&& (*tokens)->flag != CBRACKET && (*tokens)->flag != AND && (*tokens)->flag != OR)
	{
		if ((*tokens)->flag == INRED)
			io.infd = parse_inred(tokens, &err);
		else if ((*tokens)->flag == OUTRED)
			io.outfd = parse_outred(tokens, &err);
		else if ((*tokens)->flag == APPEND || (*tokens)->flag == OUTRED)
			io.outfd = parse_outred(tokens, &err);
		else if ((*tokens)->flag == HERDOC)
			parse_heredoc(tokens);
		else
			add_back_cmdlist(&cmdlist, create_cmd_list((*tokens)->token));
		if (err != 0)
			break ;
		*tokens = (*tokens)->next;
	}
	tree->errorflag = err;
	tree->cmdlist = cmdlist;
	tree->left = NULL;
	tree->right = NULL;
	tree->type = CMDLIST;
	tree->infd = io.infd;
	tree->outfd = io.outfd;
	return (tree);
}

t_tree	*parse_cmdlist(t_tokens **tokens)
{
	t_tree	*tree;

	tree  = parse_redirections(tokens);
	if (!tree)
		return (NULL);
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
	}
	return (tree);
}

t_tree  *parse_pipeline(t_tokens **tokens)
{
	t_tree  *tree;

	tree = parse_command(tokens);
	if (!tree)
		return (NULL);
	while (*tokens && (*tokens)->flag == PIPE)
		tree  = create_tree(tree, parse_command(tokens), *tokens, 0);
	return (tree);
}

t_tree  *parse_cmdline(t_tokens **tokens)
{
	t_tree  *tree;

	tree  = NULL;
	tree  = parse_pipeline(tokens);
	if (!tree)
		return (NULL);
	while ((*tokens) && ((*tokens)->flag == AND || (*tokens)->flag == OR))
	{
		*tokens = (*tokens)->next;
		tree = create_tree(tree, parse_pipeline(tokens), (*tokens)->previous, 0);
	}
	return (tree);
}

t_tree	*parser(t_tokens **tokens)
{
	t_tree	*tree;

	tree = NULL;
	tree = parse_cmdline(tokens);
	return (tree);
}
