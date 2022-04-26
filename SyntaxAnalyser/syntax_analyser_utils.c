/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:06:07 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 23:43:13 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cpar_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	pre_flag = -1;
	status = 0;
	if (tokens->previous->flag == SPACE)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (!is_string(pre_flag) && pre_flag != CBRACKET)
	{
		print_syntax_error(tokens->token);
		status = 2;
	}
	set_status(status);
}

void	check_cpar_right(t_tokens *tokens)
{
	int	next_flag;
	int	status;
	int	tmp;

	status = 0;
	tmp = 0;
	next_flag = -1;
	if (!tokens->next || (tokens->next->flag == SPACE && !tokens->next->next))
		return ;
	if (tokens->next->flag == SPACE)
	{
		next_flag = tokens->next->next->flag;
		tmp = 1;
	}
	else
		next_flag = tokens->next->flag;
	if (next_flag <= PIPE && next_flag >= BG
		&& next_flag != CBRACKET && !isredirect(next_flag))
	{
		if (tmp == 1)
			print_syntax_error(tokens->next->next->token);
		else
			print_syntax_error(tokens->next->token);
		status = 2;
	}
	set_status(status);
	return ;
}

void	check_opar_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	status = 0;
	pre_flag = -1;
	if (!tokens->previous
		|| (tokens->previous->flag == SPACE && !tokens->previous->previous))
		return ;
	else if (tokens->previous->flag == SPACE)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (pre_flag != AND && pre_flag != OR
		&& pre_flag != PIPE && pre_flag != OBRACKET)
	{
		print_syntax_error(tokens->token);
		status = 2;
	}
	set_status(status);
}

void	check_opar_right(t_tokens *tokens)
{
	int	next_flag;
	int	tmp;
	int	status;

	tmp = 0;
	status = 0;
	if (tokens->next->flag == SPACE && tokens->next->next)
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
		set_status(2);
	}
}
