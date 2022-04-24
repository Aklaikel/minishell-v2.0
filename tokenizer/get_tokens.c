/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:07:25 by osallak           #+#    #+#             */
/*   Updated: 2022/04/19 19:40:54 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_single_quote(t_tokens **head, char *input)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != '\'')
		i++;
	get_tokens(head, input, 1, SQUOTE);
	input++;
	get_tokens(head, input, i - 1, WORD);
	input += i - 1;
	if (*input == '\'')
		get_tokens(head, input, 1, SQUOTE);
	return (i + 1);
}

int	tokenize_quotes(t_tokens **head, char *input)
{
	int	i;
	int	tmp;
	int	k;

	tmp = 1;
	if (input[0] == '\'')
		return (tokenize_single_quote(head, input));
	get_tokens(head, input, 1, DQUOTE);
	input++;
	i = 0;
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$' && isword(input[i + 1]))
		{
			get_tokens(head, input, i, WORD);
			input += i;
			k = tokenize_variables(head, input);
			input += k;
			tmp += k;
			i = 0;
			continue ;
		}
		i++;
		tmp++;
	}
	input += get_tokens(head, input, i, WORD);
	if (*input == '"')
		get_tokens(head, input, 1, DQUOTE);
	return (tmp + 1);
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
	return (ft_isalnum(c) || c == '_' || c == '?');
}

static bool	is_not_token(char c)
{
	return (c != ' ' && c != '$' && c != '\'' && c != '"'
		&& c != '|' && c != '<' && c != '>' && c != '&'
		&& c != '(' && c != ')');
}
int	tokenize_word(t_tokens **head, char *input, int flag)
{
	int	i;

	i = 0;
	if (*input == '$')
		return (get_tokens(head, input, 1, WORD));
	while (input[i] && is_not_token(input[i]))
		i++;
	get_tokens(head, input, i, flag);
	return (i);
}

int	get_tokens(t_tokens **head, char *input, int len, int flag)
{
	if (len == 0)
		return (0);
	add_back_dll(head, init_list_dll(collect(ft_substr(input, 0, len)), flag));
	return (len);
}

int	tokenize_variables(t_tokens **head, char *input)
{
	int	i;

	i = 1;
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
