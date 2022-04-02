/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:07:25 by osallak           #+#    #+#             */
/*   Updated: 2022/04/01 22:50:33 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	isword(int c)
{
	return (c != ' ' && c != '|' && c != '&' && c != '\''
		&& c != '\"' && c != '>' && c != '<' && c != '(' && c != ')');
}

int	tokenize_word(t_tokens **head, char *input, int flag)
{
	int	i;

	i = 0;
	while (input[i] && isword(input[i]))
		i++;
	get_tokens(head, input, i, flag);
	return (i);
}

int	get_tokens(t_tokens **head, char *input, int len, int flag)
{
	add_back_dll(head, init_list_dll(collect(ft_substr(input, 0, len)), flag));
	// printf("%s\n", ft_substr(input, 0, len));
	return (len);
}
