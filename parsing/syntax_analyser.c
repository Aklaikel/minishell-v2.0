/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:05:15 by osallak           #+#    #+#             */
/*   Updated: 2022/04/24 18:09:31 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	init_flags(t_pcn_flags *flags, t_tokens *tokens)
{
	if (tokens)
		flags->curr = tokens->flag;
	else
		flags->curr = -1;
	if (tokens->previous)
		flags->prev = tokens->previous->flag;
	else
		flags->prev = -1;
	if (tokens->next)
		flags->next = tokens->next->flag;
	else
		flags->next = -1;
}

static int	get_next_flag(t_tokens *token)
{
	if (token && token->next && token->next->next)
		return (token->next->next->flag);
	return (-1);
}

void	check_red_tokens(t_tokens *tokens)
{
	t_pcn_flags	pcn;
	int			error;

	error = 0;
	while (tokens)
	{
		if (isredirect(tokens->flag))
		{
			init_flags(&pcn, tokens);
			if (pcn.next == SPACE)
			{
				pcn.next = get_next_flag(tokens);
				if (!is_string(pcn.next))
					error = 2;
			}
			else if (!is_string(pcn.next) && tokens->next)
				error = 3;
			else if (!is_string(pcn.next))
				error = 2;
			if (error != 0)
				break ;
		}
		tokens = tokens->next;
	}
	if (error == 2)
	{
		ft_printf("minishell-v2.0: syntax error near unexpected token `newline'\n");
		// set_status(2);
	}
	else if (error == 3)
		ft_printf("minishell-v2.0: syntax error near unexpected token `%s'\n", tokens->next->token);
}
