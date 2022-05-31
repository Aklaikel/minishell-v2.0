/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:22:08 by osallak           #+#    #+#             */
/*   Updated: 2022/05/28 17:18:27 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmdlist	*init_cmdlist(t_tokens *token)
{
	t_cmdlist	*new;

	new  = (t_cmdlist *)collect(malloc(sizeof(t_cmdlist)));
	new->cmd = token->token;
	new->type = token->flag;
	new->next = NULL;
	return (new);
}

void	add_back_cmdlist(t_cmdlist **head, t_cmdlist *new)
{
	t_cmdlist	*tmp;

	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
