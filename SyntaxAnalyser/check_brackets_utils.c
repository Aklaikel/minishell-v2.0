/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:58:16 by osallak           #+#    #+#             */
/*   Updated: 2022/06/10 08:36:00 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_opar(t_tokens *tokens)
{
	int	status;

	status = 0;
	if (tokens->flag == OBRACKET)
	{
		status = check_opar_right(tokens);
		if (status == 0)
			status = check_opar_left(tokens);
	}
	return (status);
}

int	check_cpar(t_tokens *tokens)
{
	int	status;

	status = 0;
	if (tokens->flag == CBRACKET)
	{
		status = check_cpar_right(tokens);
		if (status == 0)
			status = check_cpar_left(tokens);
	}
	return (status);
}

int	check_brackets(t_tokens *tokens)
{
	int	status;

	status = 0;
	status = check_opar(tokens);
	if (status == 0)
		status = check_cpar(tokens);
	return (status);
}
