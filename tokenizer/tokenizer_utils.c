/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:35:08 by osallak           #+#    #+#             */
/*   Updated: 2022/04/05 08:22:59 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*init_list_dll(char *input, int flag)
{
	t_tokens	*new;

	new = (t_tokens *)collect(malloc(sizeof(t_tokens)));
	new->token = ft_strdup(input);
	new->flag = flag;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	add_back_dll(t_tokens **tokens_list, t_tokens *new)
{
	t_tokens	*head;

	if (!*tokens_list)
	{
		*tokens_list = new;
		return ;
	}
	head = *tokens_list;
	while (head && head->next != NULL)
		head = head->next;
	head->next = new;
	new->previous = head;
}

t_tokens	*firstdel_dll(t_dll *dll)
{
	t_tokens	*node;

	node = dll->top;
	dll->top = dll->top->next;
	if (dll->top)
		dll->top->previous = NULL;
	(dll->len)--;
	return (node);
}

t_tokens	*lastdel_dll(t_dll *dll)
{
	t_tokens	*node;

	node = dll->bottom;
	dll->bottom = dll->bottom->previous;
	if (dll->bottom)
		dll->bottom->next = NULL;
	(dll->len)--;
	return (node);
}

t_tokens	*node_del_dll(t_dll *dll, t_tokens *node)
{
	if (!node->previous)
		return (firstdel_dll(dll));
	if (!node->next)
		return (lastdel_dll(dll));
	node->previous->next = node->next;
	node->next->previous = node->previous;
	(dll->len)--;
	return (node);
}

void	del_dll(t_dll *dll)
{
	while (dll->len)
		firstdel_dll(dll);
}
