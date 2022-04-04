/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:35:08 by osallak           #+#    #+#             */
/*   Updated: 2022/04/02 04:50:39 by aklaikel         ###   ########.fr       */
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

t_tokens	*del_last_ddl(t_dll *list)
{
	t_tokens	*node;

	list->bottom = list->bottom->previous;
	if (list->bottom)
		list->bottom->next = NULL;
	list->len--;
	return (node);
}

t_tokens	*del_first_dll(t_dll *list)
{
	t_tokens	*node;

	node = list->top;
	list->top = list->top->next;
	if (list->top)
		list->top->previous = NULL;
	list->len--;
	return (node);
}

void	del_dll_list(t_dll	*list)
{
	while (list->len)
		del_first_dll(list);
}
