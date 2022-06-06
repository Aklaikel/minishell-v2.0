/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:35:08 by osallak           #+#    #+#             */
/*   Updated: 2022/06/06 08:44:30 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static t_tokens	*ft_lstlast1(t_tokens *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_tokens	*init_list_dll(char *input, int flag)
{
	t_tokens	*new;

	new = (t_tokens *)collect(malloc(sizeof(t_tokens)));
	new->token = collect(ft_strdup(input));
	new->flag = flag;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	add_back_dll(t_tokens **tokens_list, t_tokens *new)
{
	t_tokens	*head;

	if (!tokens_list || !*tokens_list)
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

t_tokens	*lastdel_dll(t_tokens	**dll)
{
	t_tokens	*node;
	t_tokens	*lst;

	lst = ft_lstlast1(*dll);
	node = lst;
	lst = lst->previous;
	if (lst)
		lst->next = NULL;
	return (node);
}

t_tokens	*node_del_dll(t_tokens	**dll, t_tokens *node)
{
	if (!node->next && !node->previous)
	{
		*dll = NULL;
		return (node);
	}
	else if (!node->previous)
	{
		*dll = (*dll)->next;
		return (node);
	}
	else if (!node->next)
		return (lastdel_dll(dll));
	node->previous->next = node->next;
	node->next->previous = node->previous;
	return (node);
}
