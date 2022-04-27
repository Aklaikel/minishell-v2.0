/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:59:56 by osallak           #+#    #+#             */
/*   Updated: 2022/04/26 11:36:51 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char **env)
{
	t_env	*head;
	int		i;

	i = -1;
	head = NULL;
	while (env[++i])
		add_back_env(&head, add_new_env(env[i]));
	return (head);
}
