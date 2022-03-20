/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:31:29 by osallak           #+#    #+#             */
/*   Updated: 2022/03/20 20:35:33 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gc	*add_new(void *garbage)
{
	t_gc	*new;

	new = (t_gc *)malloc (sizeof(t_gc));
	if (!new)
		clear_exit;
	new->content = garbage;
	
}
