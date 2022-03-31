/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 09:49:59 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;

	while (*input)
	{
		if (input == '|')
			tokenize_pipe(input + i);
		else if (input[i] == '>' || input[i] == '<')
			tokenize_redirection(input + i);
		else if (input[i] == '&')
			tokenize_and(input + i);
		else if (input[i] == ' ')
			tokenize_space(input + i);
		else if (input[i] == '(' || input[i] == ')')
			tokenize_brackets(input + i);
		else if (input[i] == '\"' || input[i] == '\'')
			tokenize_quotes(input + i);
		else
			tokenize_word(&tokens, input);
	}
}
