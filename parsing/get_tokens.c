/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:07:25 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 09:47:31 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_pipe(t_tokens **head, char *input)
{
	if (input[1] == '|')
	{
		add_back_dll(head, init_list_dll(collect(ft_strdup("||")), OR));
		input++;
	}
	else
		add_back_dll(head, init_list_dll(collect(ft_strdup("|")), PIPE));
	input++;
}

void	tokenize_redirection(t_tokens **head, char *input)
{
	if (input[1] == '>' || input[1] == '<')
	{
		add_back_dll(head, \
			init_list_dll(collect(ft_substr(input, 0, 2)), REDIRECTION));
		input++;
	}
	else
		init_list_dll(collect(ft_substr(input, 0, 1)), REDIRECTION);
	input++;
}

void	tkenize_and(t_tokens **head, char *input)
{
	if (input[1] == '&')
	{
		add_back_dll(head, \
			init_list_dll(collect(ft_substr(input, 0, 2)), AND));
		input++;//!needs some modifications
	}
	else
		init_list_dll(collect(ft_substr(input, 0, 1)), AND);
}

void	tokenize_space(t_tokens **head, char *input)
{
	init_list_dll(collect(ft_strdup(" ")), SPACE);//todo skip all white spaces
	input
}
