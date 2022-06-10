/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unwanted_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:05:05 by osallak           #+#    #+#             */
/*   Updated: 2022/06/09 16:45:20 by osallak          ###   ########.fr       */
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
			if (!node->next || node->next->flag != node->flag)
			{
				node_del_dll(tokens, node);
				node = *tokens;
				continue ;
			}
			else
			{
				node->flag = WORD;
				node->token = collect(ft_strdup(""));
				continue ;
			}
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
