/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:12:13 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 10:56:35 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	clear_exit(void)
{
	t_gc	*tmp;

	while (g_global.g_garbage)
	{
		tmp = g_global.g_garbage;
		g_global.g_garbage = g_global.g_garbage->next;
		free(tmp->content);
		free(tmp);
	}
	exit(0);
}
