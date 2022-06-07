/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/06 17:03:07 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(t_env *env)
{
	char	*tildev;

	tildev = find_env("HOME", env);
	return (tildev);
}

void	expand_wildcard(t_tokens **tokens)
{
	DIR				*dir;
	struct dirent	*entity;
	t_tokens		*newlist;
	t_tokens		*tmp;

	(void)tokens;
	dir = opendir(".");
	if (!dir)
		return (perror(NULL));
	newlist = NULL;
	while (true)
	{
		entity = readdir(dir);
		if (!entity)
			break ;
		if (entity->d_name[0] != '.')
			add_back_dll(&newlist, init_list_dll \
				(collect(ft_strdup(entity->d_name)), WORD));
	}
	tmp = newlist;
	if (!(*tokens)->next)
		(*tokens)->next = newlist;
	else
		add_back_dll(&newlist, (*tokens)->next);
	(*tokens)->next = newlist;
}

static char	*expand_variables(t_tokens *node, t_env *env)
{
	if (!strncmp(node->token, "$?", 2))
		return (collect(ft_itoa(g_global.exit_status)));
	if (!strncmp(node->token, "$0", 2))
		return ((char *)collect(ft_strdup("minishell")));
	else
		return (find_env(node->token + 1, env));
}

void	expander(t_env *env, t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == VAR)
			node->token = expand_variables(node, env);
		else if (node->flag == WC)
		{
			expand_wildcard(&node);
			node_del_dll(tokens, node);
		}
		else if (node->flag == TILDE)
		{
			node->token = expand_tilde(env);
			node->flag = WORD;
		}
		node = node->next;
	}
}
