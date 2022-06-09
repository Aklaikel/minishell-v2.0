/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:58:16 by osallak           #+#    #+#             */
/*   Updated: 2022/06/09 07:50:52 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_opar(t_tokens *tokens)
{
	if (tokens->flag == OBRACKET)
	{
		check_opar_right(tokens);
		if (g_global.exit_status == 0)
			check_opar_left(tokens);
	}
}

void	check_cpar(t_tokens *tokens)
{
	if (tokens->flag == CBRACKET)
	{
		check_cpar_right(tokens);
		if (g_global.exit_status == 0)
			check_cpar_left(tokens);
	}
}

void	check_brackets(t_tokens *tokens)
{
	check_opar(tokens);
	check_cpar(tokens);
}
