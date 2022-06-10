/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_or_pipe_bg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:57:47 by osallak           #+#    #+#             */
/*   Updated: 2022/06/10 08:27:05 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_or_pipe_bg_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	pre_flag = -1;
	status = 0;
	if (!tokens->previous
		|| (tokens->previous->flag == _SPACE && !tokens->previous->previous))
		status = 2;
	else if (tokens->previous->flag == _SPACE)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (!is_string(pre_flag) && pre_flag != CBRACKET)
		status = 2;
	if (status == 2)
		print_syntax_error(tokens->token);
	return (status);
}

int	check_and_or_pipe_bg_right(t_tokens *tok)
{
	int	next;
	int	status;

	status = 0;
	next = -1;
	if ((!tok->next || (tok->next->flag == _SPACE && !tok->next->next)))
		status = 2;
	else if (tok->next->flag == _SPACE)
		next = tok->next->next->flag;
	else
		next = tok->next->flag;
	if (!is_string(next) && !isredirect(next) && next != OBRACKET)
		status = 2;
	if (status == 2)
		print_syntax_error(tok->token);
	return (status);
}

int	check_and_or_pipe_bg(t_tokens *tokens)
{
	int	status;

	status = 0;
	status = check_and_or_pipe_bg_left(tokens);
	if (status == 0)
		status = check_and_or_pipe_bg_right(tokens);
	return (status);
}
