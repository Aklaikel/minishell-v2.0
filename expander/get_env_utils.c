/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:19:22 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 16:18:44 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *line)
{
	int		len;

	len = 0;
	while (len[line] != '=' && len[line])
		len++;
	return (collect(ft_substr(line, 0, len)));
}

char	*get_value(char *line)
{
	int	start;

	start = 0;
	while (start[line] != '=' && start[line])
		start++;
	return (collect(ft_strdup(line + start + 1)));
}

t_env	*add_new_env(char *line)
{
	t_env	*node;

	node = (t_env *)collect(malloc(sizeof(t_env)));
	node->next = NULL;
	node->env_name = get_name(line);
	node->env_value = get_value(line);
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
