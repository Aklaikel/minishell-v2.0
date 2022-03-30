/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:35:08 by osallak           #+#    #+#             */
/*   Updated: 2022/03/30 18:30:47 by aklaikel         ###   ########.fr       */
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
	new->previous = NULL; //todo
	return (new);
}

void	add_back_dll(t_tokens **tokens_list, t_tokens *new)
{
	t_tokens	*head;

	head = *tokens_list;
	while (head->next != NULL)
		head = head->next;
	head->next = new;
	new->previous = head;
}
