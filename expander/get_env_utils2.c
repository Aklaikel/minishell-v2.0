/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:31:00 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/11 08:13:58 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static t_env	*get_last(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (*lst == NULL)
		*lst = new;
	else
	{	
		last_node = get_last(*lst);
		last_node->next = new;
	}
}
