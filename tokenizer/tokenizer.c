/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:39 by osallak           #+#    #+#             */
/*   Updated: 2022/06/06 16:56:46 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	tokenizer_helper1(t_tokens **tokens, char *input)
{
	int	i;

	i = 0;
	if (*input == '|' && *(input + 1) != '|')
		i = get_tokens(tokens, input, 1, PIPE);
	else if (*input == '|' && *(input + 1) == '|')
		i = get_tokens(tokens, input, 2, OR);
	else if (*input == '&' && *(input + 1) == '&')
		i = get_tokens(tokens, input, 2, AND);
	else if (*input == ' ')
		i = tokenize_space(tokens, input);
	else if (*input == '"' || *input == '\'')
		i = tokenize_quotes(tokens, input);
	else if ((*input == '>' && *(input + 1) == '>'))
		i = get_tokens(tokens, input, 2, APPEND);
	return (i);
}

static int	tokenizer_helper2(t_tokens **tokens, char *input)
{
	int	i;

	i = 0;
	if ((*input == '>' && *(input + 1) != '>'))
		i = get_tokens(tokens, input, 1, OUTRED);
	else if ((*input == '<' && *(input + 1) == '<'))
		i = get_tokens(tokens, input, 2, HERDOC);
	else if ((*input == '<' && *(input + 1) != '<'))
		i = get_tokens(tokens, input, 1, INRED);
	else if (*input == '(')
		i = get_tokens(tokens, input, 1, OBRACKET);
	else if (*input == ')')
		i = get_tokens(tokens, input, 1, CBRACKET);
	return (i);
}

static int	tokenizer_helper3(t_tokens **tokens, char *input)
{
	int	i;

	i = 0;
	if (*input == '$' && (ft_isalpha(*(input + 1))
			|| *(input + 1) == '_' || *(input + 1) == '?'
			|| *(input + 1) == '0'))
		i = tokenize_variables(tokens, input);
	else if (*input == '*')
		i = tokenize_wildcard(tokens, input);
	else if (*input == '~' && (!*(input + 1)
			|| *(input + 1) == '/' || *(input + 1) == ' ' ))
		i = get_tokens(tokens, input, 1, TILDE);
	else
			i = tokenize_word(tokens, input, WORD);
	return (i);
}

static int	tokenizer_helper4(t_tokens **tokens, char *input)
{
	int	i;

	i = 0;
	i += tokenizer_helper1(tokens, input);
	i += tokenizer_helper2(tokens, input);
	i += tokenizer_helper3(tokens, input);
	return (i);
}

t_tokens	*tokenizer(char *input)
{
	t_tokens	*tokens;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(input);
	tokens = NULL;
	while (*input && i < len)
	{
		i = tokenizer_helper4(&tokens, input);
		input += i;
	}
	return (tokens);
}
