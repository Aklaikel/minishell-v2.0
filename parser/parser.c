/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 07:34:48 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 17:26:00 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_outred(t_tokens **token, int *err)
{
	int	fd;
	int	flags;

	if ((*token)->flag == APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	*token = (*token)->next;
	fd = open((*token)->token, flags, 0666);
	if (fd == -1)
	{
		*err = errno;
		return (-1);
	}
	return (fd);
}

t_tree	*parse_command(t_tokens **tokens)
{
	t_tree	*tree;

	if (!*tokens)
		return (NULL);
	tree = parse_cmdlist(tokens);
	if (!tree && (*tokens)->flag == OBRACKET)
	{
		*tokens = (*tokens)->next;
		tree = parse_cmdline(tokens);
		if (!tree)
			return (NULL);
		if (*tokens && (*tokens)->flag == CBRACKET)
			*tokens = (*tokens)->next;
	}
	return (tree);
}

t_tree	*parse_pipeline(t_tokens **tokens)
{
	t_tree	*tree;
	t_tree	*tmp;

	if (!*tokens)
		return (NULL);
	tree = parse_command(tokens);
	if (!tree)
		return (NULL);
	while (*tokens && (*tokens)->flag == PIPE)
	{
		*tokens = (*tokens)->next;
		tmp = parse_command(tokens);
		if (!tmp)
			return (NULL);
		tree = connect_tree(tree, tmp, PIPE);
	}
	return (tree);
}

t_tree	*parse_cmdline(t_tokens **tokens)
{
	t_tree	*tree;
	t_tree	*tmp;
	int		type;

	tree = NULL;
	tree = parse_pipeline(tokens);
	if (!tree)
		return (NULL);
	while (*tokens && ((*tokens)->flag == AND || (*tokens)->flag == OR))
	{
		type = (*tokens)->flag;
		*tokens = (*tokens)->next;
		tmp = parse_pipeline(tokens);
		if (!tmp)
		{
			return (NULL);
		}
		tree = connect_tree(tree, tmp, type);
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
