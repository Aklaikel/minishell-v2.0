/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:17:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/05 09:16:49 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(t_env *env)
{
	char	*tildev;

	tildev = find_env("HOME", env);
	return (tildev);
}

char	*expand_wildcard(void)
{
	char *wildcv = NULL;

	return wildcv;
}
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
			if (!strncmp(node->token, "$0", 2))
				node->token = (char *)collect(ft_strdup("minishell"));
			else
				node->token = find_env(node->token + 1, env);
		}
		else if (node->flag == WC)
			node->token = expand_wildcard();
		else if (node->flag == TILDE)
			node->token = expand_tilde(env);
		node = node->next;
	}
}
