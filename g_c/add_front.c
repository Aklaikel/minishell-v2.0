/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:25:50 by osallak           #+#    #+#             */
/*   Updated: 2022/03/20 22:42:52 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_front(t_gc *new)
{
	if (!new)
		return ;
	if (!g_garbage)
		g_garbage = new;
	else
	{
		new->next = g_garbage;
		g_garbage = new;
	}
}
