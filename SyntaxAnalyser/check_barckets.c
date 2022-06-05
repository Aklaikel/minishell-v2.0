/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_barckets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:33:08 by osallak           #+#    #+#             */
/*   Updated: 2022/06/05 18:47:20 by osallak          ###   ########.fr       */
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
	return (flag == WORD || flag == VAR || flag == SQUOTE || flag == DQUOTE
		|| flag == TILDE || flag == WC);
}

void	print_syntax_error(char *error)
{
	ft_printf
		("minishell-v2.0: syntax error near unexpected token: `%s'\n", error);
}
