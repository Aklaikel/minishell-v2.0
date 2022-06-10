/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basic_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:00:46 by osallak           #+#    #+#             */
/*   Updated: 2022/06/10 08:37:23 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbalanced_quotes(t_tokens *head)
{
	int		dquot;
	int		squot;

	dquot = 0;
	squot = 0;
	while (head)
	{
		if (head->flag == DQUOTE)
			dquot++;
		if (head->flag == SQUOTE)
			squot++;
		head = head->next;
	}
	if (dquot % 2 != 0)
	{
		ft_printf("unexpected EOL while looking for matching `\"'\n");
		return (2);
	}
	else if (squot % 2 != 0)
	{
		ft_printf("unexpected EOL while looking for matching `\''\n");
		return (2);
	}
	return (0);
}

int	isbalanced_brackets(t_tokens *head)
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
			ft_printf("minishell: Syntax error near unexpected token `)'\n");
			return (2);
		}
		node = node->next;
	}
	if (flag != 0)
	{
		print_syntax_error("newline");
		return (2);
	}
	return (0);
}
