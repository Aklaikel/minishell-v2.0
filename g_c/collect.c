/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:50:21 by osallak           #+#    #+#             */
/*   Updated: 2022/05/30 08:19:45 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	*collect(void *gb)
{
	if (!gb)
	{
		perror(NULL);
		clear_exit();
	}
	add_front(add_new(gb));
	return (gb);
}
