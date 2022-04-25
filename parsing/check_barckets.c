/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_barckets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:33:08 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 11:43:23 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isredirect(int flag)
{
	return (flag == OUTRED || flag == INRED
		|| flag == APPEND || flag == HERDOC);
}

bool	is_string(int flag)
{
	return (flag == WORD || flag == VAR);
}

void	print_syntax_error(char *error)
{
	ft_printf
		("minishell-v2.0: syntax error near unexpected token: `%s'\n", error);
}

void	check_cpar(t_tokens *tokens)
{
	t_pcn_flags	flags;

	while (tokens)
	{
		init_flags(&flags, tokens);
		if (flags.curr == CBRACKET)
		{
			check_cpar_right(tokens);
			if (g_global.exit_status == 0)
				check_cpar_left(tokens);
			if (g_global.exit_status != 0)
				break ;
		}
		tokens = tokens->next;
	}
}

void	check_opar(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->flag == OBRACKET)
		{
			check_opar_right(tokens);
			if (g_global.exit_status == 0)
				check_opar_left(tokens);
			if (g_global.exit_status != 0)
				break ;
		}
		tokens = tokens->next;
	}
}