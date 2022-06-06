/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:38 by osallak           #+#    #+#             */
/*   Updated: 2022/06/06 17:22:37 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isword(int c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

bool	is_not_token(char c)
{
	return (c != ' ' && c != '$' && c != '\'' && c != '"'
		&& c != '|' && c != '<' && c != '>'
		&& c != '(' && c != ')' && c != '*');
}

int	tokenize_wildcard(t_tokens **head, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == '*')
		i++;
	get_tokens(head, input, 1, WC);
	return (i + 1);
}

int	tokenize_variables(t_tokens **head, char *input)
{
	int	i;

	i = 1;
	if (*(input + 1) == '?' || *(input + 1) == '0')
		return (get_tokens(head, input, 2, VAR));
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

void	tokenize_quotes_helper(t_tokens **head, char *input, int i)
{
	input += get_tokens(head, input, i, WORD);
	if (*input == '"')
		get_tokens(head, input, 1, DQUOTE);
}
