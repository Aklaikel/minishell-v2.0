/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 10:15:39 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;

	while (*input)
	{
		if (*input == '|')
			gettokens(&tokens, input);
		else if (*input == '>' || *input == '<')
			tokenize_redirection(&tokens, input);
		else if (*input == '&')
			tokenize_and(&tokens, input);
		else if (*input == ' ')
			tokenize_space(&tokens, input);
		else if (*input == '(' || *input == ')')
			tokenize_brackets(&tokens, input);
		else if (*input == '\"' || *input == '\'')
			tokenize_quotes(&tokens, input);
		else
			tokenize_word(&tokens, input);
	}
}
