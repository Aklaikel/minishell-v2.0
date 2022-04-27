/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:19:22 by osallak           #+#    #+#             */
/*   Updated: 2022/04/26 19:05:08 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_new_env(char *line)
{
	t_env	*node;

	node = (t_env *)collect(malloc(sizeof(t_env)));
	node->next = NULL;
	node->env_line = collect(ft_strdup(line));
	return (node);
}

void	add_back_env(t_env **head, t_env *new)
{
	t_env	*node;

	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node && node->next)
		node = node->next;
	node->next = new;
}
