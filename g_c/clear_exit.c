/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:12:13 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 17:59:48 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	clear_exit(int status)
{
	t_gc	*tmp;

	while (g_global.g_garbage)
	{
		tmp = g_global.g_garbage;
		g_global.g_garbage = g_global.g_garbage->next;
		free(tmp->content);
		free(tmp);
	}
	exit(status);
}
