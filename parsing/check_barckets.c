/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_barckets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:33:08 by osallak           #+#    #+#             */
/*   Updated: 2022/04/24 18:08:55 by osallak          ###   ########.fr       */
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
	// exit_status = 2;
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
			check_cpar_left(tokens);
		}
		tokens = tokens->next;
	}
}

void	check_opar(t_tokens *tokens)
{
	t_pcn_flags	pcn;

	while (tokens)
	{
		if (tokens->flag == OBRACKET)
		{
			init_flags(&pcn, tokens);
			check_opar_right(tokens);
			// if (status != 0)
			// 	break ;
			check_opar_left(tokens);
			// if (status != 0)
			// 	break ;
		}
		tokens = tokens->next;
	}
}