/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/05 18:47:36 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(t_env *env)
{
	char	*tildev;

	tildev = find_env("HOME", env);
	return (tildev);
}

void	insert_node(t_tokens **tokens, char *filename)
{
	t_tokens	*tmp;

	if (!*tokens)
	{
		*tokens = init_list_dll(filename, WORD);
		return ;
	}
	if (!(*tokens)->next)
	{
		(*tokens)->next = init_list_dll(filename, WORD);
		return ;
	}
	tmp = (*tokens)->next;
	(*tokens)->next = init_list_dll(filename, WORD);
	(*tokens)->next->previous = (*tokens);
	tmp->previous = (*tokens)->next;
	(*tokens)->next->next = tmp;
}

void	expand_wildcard(t_tokens **tokens)
{
	DIR				*dir;
	struct dirent	*entity;
	t_tokens		*newlist;

	dir = opendir(".");
	if (!dir)
		return (perror(NULL));
	newlist = NULL;
	while (true)
	{
		entity =  readdir(dir);
		if (!entity)
			break ;
		if (entity->d_name[0] != '.')
			add_back_dll(&newlist, init_list_dll(collect(ft_strdup(entity->d_name)), WORD));
	}
	add_back_dll(&newlist, (*tokens)->next);
	(*tokens)->next = newlist;
}

void	expander(t_env *env, t_tokens *tokens)
{
	t_tokens	*node;

	node = tokens;
	while (node)
	{
		if (node->flag == VAR)
		{
			if (!strncmp(node->token, "$?", 2))
				node->token = (char *)collect(ft_strdup("must be replaced with the exit status\n"));
			if (!strncmp(node->token, "$0", 2))
				node->token = (char *)collect(ft_strdup("minishell"));
			else
				node->token = find_env(node->token + 1, env);
		}
		else if (node->flag == WC)
		{
			node_del_dll(&tokens, node);
			expand_wildcard(&node);
		}
		else if (node->flag == TILDE)
		{
			node->token = expand_tilde(env);
			node->flag = WORD;
		}
		node = node->next;
	}
}
