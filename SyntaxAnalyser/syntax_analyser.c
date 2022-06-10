/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:05:15 by osallak           #+#    #+#             */
/*   Updated: 2022/06/10 08:28:34 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	syntax_analyser(t_tokens *tokens)
{
	int	status;

	status = 0;
	isbalanced_brackets(tokens);
	isbalanced_quotes(tokens);
	while (tokens && status == 0)
	{
		if (tokens->flag == PIPE || tokens->flag == AND || tokens->flag == OR)
			status = check_and_or_pipe_bg(tokens);
		else if (isredirect(tokens->flag))
			status = check_red_tokens(tokens);
		else if (tokens->flag == OBRACKET || tokens->flag == CBRACKET)
			status = check_brackets(tokens);
		tokens = tokens->next;
	}
	return (status);
}

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

int	get_next_flag(t_tokens *token)
{
	if (token && token->next && token->next->next)
		return (token->next->next->flag);
	return (-1);
}

int	check_red_tokens(t_tokens *toks)
{
	int	next_flag;
	int	status;

	status = 0;
	next_flag = -1;
	if (!toks->next || (toks->next->flag == _SPACE && !toks->next->next))
		status = 2;
	else if (toks->next->flag == _SPACE)
		next_flag = toks->next->next->flag;
	else
		next_flag = toks->next->flag;
	if (!is_string(next_flag))
		status = 2;
	if (status == 2)
	{
		if (!toks->next || (toks->next->flag == _SPACE && !toks->next->next))
			print_syntax_error("newline");
		else if (toks->next->flag == _SPACE)
			print_syntax_error(toks->next->next->token);
		else
			print_syntax_error(toks->next->token);
	}
	return (status);
}
