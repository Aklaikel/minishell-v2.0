/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/03/30 20:58:31 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			tokenize_pipe(input + i);
		else if (input[i] == '>' || input[i] == '<')
			tokenize_redirection(input + i);
		else if (input[i] == '&')
			tokenize_and(input + i);
		else if (input[i] == ' ')
			tokenize_space(input + i);
		else if (input[i] == '(' || input[i] == ')')
			tokenize_brackets(input + i);
		else
			tokenize_word(input + i);
		i++;
	}
}
