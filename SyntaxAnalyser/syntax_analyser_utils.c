/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:06:07 by osallak           #+#    #+#             */
/*   Updated: 2022/06/10 08:40:31 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cpar_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	pre_flag = -1;
	status = 0;
	if (tokens->previous->flag == _SPACE)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (!is_string(pre_flag) && pre_flag != CBRACKET)
	{
		print_syntax_error(tokens->token);
		status = 2;
	}
	return (status);
}

int	check_cpar_right_helper(t_tokens *tokens, int tmp)
{
	if (tmp == 1)
		print_syntax_error(tokens->next->next->token);
	else
		print_syntax_error(tokens->next->token);
	return (2);
}

int	check_cpar_right(t_tokens *tokens)
{
	int	next_flag;
	int	status;
	int	tmp;

	status = 0;
	tmp = 0;
	next_flag = -1;
	if (!tokens->next || (tokens->next->flag == _SPACE && !tokens->next->next))
		return (0);
	if (tokens->next->flag == _SPACE)
	{
		next_flag = tokens->next->next->flag;
		tmp = 1;
	}
	else
		next_flag = tokens->next->flag;
	if (next_flag != PIPE && next_flag != OR && next_flag != AND && next_flag != CBRACKET && !isredirect(next_flag))
	{
		if (tmp == 1)
			print_syntax_error(tokens->next->next->token);
		else
			print_syntax_error(tokens->next->token);
		status = 2;
	}
	return (status);
}

int	check_opar_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	status = 0;
	pre_flag = -1;
	if (!tokens->previous
		|| (tokens->previous->flag == _SPACE && !tokens->previous->previous))
		return (0);
	else if (tokens->previous->flag == _SPACE)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (pre_flag != AND && pre_flag != OR
		&& pre_flag != PIPE && pre_flag != OBRACKET)
	{
		print_syntax_error(tokens->token);
		status = 2;
	}
	return (status);
}

int	check_opar_right(t_tokens *tokens)
{
	int	next_flag;
	int	tmp;
	int	status;

	tmp = 0;
	status = 0;
	if (tokens->next->flag == _SPACE && tokens->next->next)
	{
		next_flag = tokens->next->next->flag;
		tmp = 1;
	}
	else
		next_flag = tokens->next->flag;
	if (!is_string(next_flag)
		&& !isredirect(next_flag) && next_flag != OBRACKET)
	{
		if (tmp)
			print_syntax_error(tokens->next->next->token);
		else
			print_syntax_error(tokens->next->token);
	}
	return (status);
}
