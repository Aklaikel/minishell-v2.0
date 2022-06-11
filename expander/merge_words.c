/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:28:48 by osallak           #+#    #+#             */
/*   Updated: 2022/06/11 08:14:07 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_words(t_tokens **head)
{
	t_tokens	*tokens;

	tokens = *head;
	while (tokens && tokens->next)
	{
		if (tokens->flag == WORD && tokens->next->flag == WORD)
		{
			tokens->token
				= collect(ft_strjoin(tokens->token, tokens->next->token));
			node_del_dll(head, tokens->next);
			tokens = *head;
			continue ;
		}
		tokens = tokens->next;
	}
}
