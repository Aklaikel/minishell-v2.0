/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:44:32 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 15:45:29 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*cmdlist_hlpr1(t_tree *tree, int err, t_cmdlist *lst, struct s_io io)
{
	tree->errorflag = err;
	tree->cmdlist = lst;
	tree->left = NULL;
	tree->right = NULL;
	tree->type = CMDLIST;
	tree->infd = io.infd;
	tree->outfd = io.outfd;
	return (tree);
}

int	close_fd(int oldfd, int stdfd, t_tokens **tokens, int *err)
{
	int	fd;

	if (!*tokens || !(*tokens)->next)
	{
		*err = 2;
		return (-1);
	} 
	if (oldfd != stdfd)
		close(oldfd);
	if (stdfd == STDIN_FILENO)
		fd = parse_inred(tokens, err);
	else
		fd = parse_outred(tokens, err);
	return (fd);
}

int	pcmdlist_helper(t_tokens **tokens, struct s_io *io, t_cmdlist **lst)
{
	int	err;

	err = 0;

	if ((*tokens)->flag == INRED)
		io->infd = close_fd(io->infd, 0, tokens, &err);
	else if ((*tokens)->flag == APPEND || (*tokens)->flag == OUTRED)
		io->outfd = close_fd(io->outfd, 1, tokens, &err);
	else if ((*tokens)->flag == HERDOC)
		io->infd = parse_heredoc(tokens, &err);
	else
		add_back_cmdlist(lst, create_cmd_list((*tokens)->token));
	return (err);
}

t_tree	*parse_cmdlist(t_tokens **tokens)
{
	t_tree		*tree;
	t_cmdlist	*cmdlist;
	struct s_io	io;
	int			err;
	int			visited;

	if (!*tokens)
		return (NULL);
	io.infd = STDIN_FILENO;
	io.outfd = STDOUT_FILENO;
	cmdlist = NULL;
	tree = (t_tree *)collect(malloc(sizeof(t_tree)));
	visited = 0;
	err = 0;
	while (*tokens && (*tokens)->flag != PIPE
		&& (*tokens)->flag != CBRACKET && (*tokens)->flag != AND
		&& (*tokens)->flag != OR && (*tokens)->flag != OBRACKET)
	{
		visited = 1;
		err = pcmdlist_helper(tokens, &io, &cmdlist);
		if (err != 0)
			break ;
		*tokens = (*tokens)->next;
	}
	if (visited == 0)
		return (NULL);
	return (cmdlist_hlpr1(tree, err, cmdlist, io));
}