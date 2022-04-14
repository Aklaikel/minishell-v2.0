/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basic_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:00:46 by osallak           #+#    #+#             */
/*   Updated: 2022/04/13 22:40:35 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_basic_errors(t_tokens *head)
{
	int			i;
	t_tokens	*node;

	i = 0;
	node = head;
	while (node)
	{
		while (node->token[i])
		{	
			if (node->token[i] == ';' || node->token[i] == '{'
				|| node->token[i] == '}' || node->token[i] == '['
				|| node->token[i] == ']' || node->token[i] == '\\')
			{
				ft_printf("minishell: syntax error near unexpected token '%c'\n", node->token[i]);
				// set_status(2); // need to be defined
			}
			i++;
		}
		node = node->next;
	}
}

void	isbalanced_brackets(t_tokens *head)
{
	t_tokens	*node;
	int			flag;

	flag = 0;
	node = head;
	while (node)
	{
		if (node->flag == OBRACKET)
			flag++;
		else if (node->flag == CBRACKET)
			flag--;
		if (flag == -1)
		{
			ft_printf("minishell: syntax error near unexpected token ')'\n");
			// set_status(2); // need to be defined
			return ;
		}
		node = node->next;
	}
	if (flag != 0)
	{
		ft_printf("minishell: syntax error near unexpected token '('\n");
		// set_status(2); // need to be defined
	}
}
