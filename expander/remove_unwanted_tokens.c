/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unwanted_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:05:05 by osallak           #+#    #+#             */
/*   Updated: 2022/05/04 17:36:29 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == SQUOTE || node->flag == DQUOTE)
		{
			node_del_dll(tokens, node);
			node = *tokens;
			continue ;
		}
		node = node->next;
	}
}

void	remove_spaces(t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == _SPACE)
			node_del_dll(tokens, node);
		node = node->next;
	}
}
