/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:50:21 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 18:05:16 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	*collect(void *gb)
{
	if (!gb)
	{
		perror(NULL);
		clear_exit(1);
	}
	add_front(add_new(gb));
	return (gb);
}
