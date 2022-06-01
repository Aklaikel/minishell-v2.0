/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/01 13:28:18 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expander(t_tokens **tokens)
// {
// 	t_tokens	*node;

// 	node = *tokens;
// 	if (!node)
// 		return ;
// 	while (node)
// 	{
// 		if (node->flag == VAR)
// 			node->token = get_var_value(node->token);
// 		node = node->next;
// 	}
// }