/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:58:42 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 08:42:08 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->flag == PIPE)
			printf("PIPE : ");
		else if (tokens->flag == WORD)
			printf("WORD : ");
		else if (tokens->flag == OUTRED)
			printf("OUTRED : ");
		else if (tokens->flag == INRED)
			printf("INRED : ");
		else if (tokens->flag == APPEND)
			printf("APPEND : ");
		else if (tokens->flag == HERDOC)
			printf("HERDOC : ");
		else if (tokens->flag == AND)
			printf("AND : ");
		else if (tokens->flag == OR)
			printf("OR : ");
		else if (tokens->flag == _SPACE)
			printf("SPACE : ");
		else if (tokens->flag == OBRACKET)
			printf("OBRACKET : ");
		else if (tokens->flag == CBRACKET)
			printf("CBRACKET : ");
		else if (tokens->flag == SQUOTE)
			printf("SQUOTE : ");
		else if (tokens->flag == DQUOTE)
			printf("DQUOTE : ");
		else if (tokens->flag == VAR)
			printf("VAR : ");
		printf("%s\n", tokens->token);
		tokens = tokens->next;
	}
}