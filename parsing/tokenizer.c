/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 09:50:17 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;

	while (*input)
	{
		if ( == '|')
			tokenize_pipe(input + i);
		else if ( == '>' ||  == '<')
			tokenize_redirection(input + i);
		else if ( == '&')
			tokenize_and(input + i);
		else if ( == ' ')
			tokenize_space(input + i);
		else if ( == '(' ||  == ')')
			tokenize_brackets(input + i);
		else if ( == '\"' ||  == '\'')
			tokenize_quotes(input + i);
		else
			tokenize_word(&tokens, input);
	}
}
