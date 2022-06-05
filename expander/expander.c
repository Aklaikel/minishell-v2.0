/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:25 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_env *env, t_tokens *tokens)
{
	t_tokens	*node;

	node = tokens;
	while (node)
	{
		if (node->flag == VAR)
		{
			if (!strncmp(node->token, "$?", 2))
				node->token = (char *)collect(ft_strdup("must be replaced with the exit status\n"));
			else
				node->token = find_env(node->token + 1, env);
		}
		node = node->next;
	}
}
