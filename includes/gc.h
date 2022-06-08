/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:28:51 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 18:04:18 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

typedef struct s_gc
{
	void		*content;
	struct s_gc	*next;
}				t_gc;

void	add_front(t_gc *new);
t_gc	*add_new(void *garbage);
void	clear_exit(int status);
void	*collect(void *gb);

#endif
