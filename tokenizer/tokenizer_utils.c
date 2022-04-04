/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:35:08 by osallak           #+#    #+#             */
/*   Updated: 2022/04/04 23:20:19 by osallak          ###   ########.fr       */
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
