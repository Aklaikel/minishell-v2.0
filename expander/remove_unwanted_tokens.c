/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unwanted_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:05:05 by osallak           #+#    #+#             */
/*   Updated: 2022/04/26 23:18:52 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_unwanted_tokens(t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == SQUOTE
			|| node->flag == SQUOTE || node->flag == _SPACE)
			node_del_dll(tokens, node);
		node = node->next;
	}
}
