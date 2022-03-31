/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 09:50:46 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;

	while (*input)
	{
		if (*input == '|')
			tokenize_pipe(input);
		else if (*input == '>' || *input == '<')
			tokenize_redirection(input);
		else if (*input == '&')
			tokenize_and(input);
		else if (*input == ' ')
			tokenize_space(input);
		else if (*input == '(' || *input == ')')
			tokenize_brackets(input);
		else if (*input == '\"' || *input == '\'')
			tokenize_quotes(input);
		else
			tokenize_word(&tokens, input);
	}
}
