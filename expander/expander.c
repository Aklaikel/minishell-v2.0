/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 04:28:39 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expander(t_env *env, t_tokens *tokens)
// {
// 	t_tokens	*node;

// 	node = tokens;
// 	while (node)
// 	{
// 		if (node->flag == VAR)
// 			node->token = get_var_value(env, node->token + 1);
// 		node = node->next;
// 	}
// }