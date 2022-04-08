/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:07:25 by osallak           #+#    #+#             */
/*   Updated: 2022/04/08 18:21:29 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_single_quote(t_tokens **head, char *input)
{
	int	i;

	i = 0;
	get_tokens(head, input, 1, SQUOTE);
	input++;
	while (input[i] && input[i] != '\'')
		i++;
	get_tokens(head, input, i, WORD);
	input += i;
	get_tokens(head, input, 1, SQUOTE);
	return (i + 1);
}

int	tokenize_quotes(t_tokens **head, char *input)
{
	if (input[0] == '\'')
		return (tokenize_single_quote(head, input));
	
}

//skip all white spaces and tokenize just one
int	tokenize_space(t_tokens **head, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ' && input[i + 1] == ' ')
		i++;
	get_tokens(head, input, 1, SPACE);
	return (i + 1);
}

bool	isword(int c)
{
	return (c != ' ' && c != '|' && c != '&' && c != '\''
		&& c != '\"' && c != '>' && c != '<' && c != '(' && c != ')');
}

int	tokenize_word(t_tokens **head, char *input, int flag)
{
	int	i;

	i = 0;
	while (input[i] && isword(input[i]) && input[i] != '$')
		i++;
	get_tokens(head, input, i, flag);
	return (i);
}

int	get_tokens(t_tokens **head, char *input, int len, int flag)
{
	add_back_dll(head, init_list_dll(collect(ft_substr(input, 0, len)), flag));
	return (len);
}

int	tokenize_variables(t_tokens **head, char *input)
{
	int	i;

	i = 0;
	while (input[i] && isword(input[i]))
		i++;
	if (i == 1)
	{
		get_tokens(head, input, 1, WORD);
		return (1);
	}
	get_tokens(head, input, i, VAR);
	return (i);
}
