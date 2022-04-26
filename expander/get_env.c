/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:59:56 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 18:42:56 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char **av)
{
	t_env	*head;
	char	*line;
	int		i;

	while (av[i])
		add_back_env(&head, add_new_env(av[i]));
}