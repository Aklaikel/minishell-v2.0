/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:22:08 by osallak           #+#    #+#             */
/*   Updated: 2022/07/03 17:53:34 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_heredoc(t_tokens **tokens, int *err)
{
	int		fd[2];
	char	*delim;
	char	*input;

	*tokens = (*tokens)->next;
	delim = (*tokens)->token;
	if (pipe(fd) == -1)
	{
		*err = errno;
		return (-1);
	}
	while (true)
	{
		input = readline("> ");
		if (!input)
			return (*err = 1, -1);
		collect(input);
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
	new->cmd = cmd;
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
