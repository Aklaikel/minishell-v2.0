/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_HEXAA.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:39:16 by aklaikel          #+#    #+#             */
/*   Updated: 2021/11/30 17:08:47 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_HEXAA(unsigned long num, int *len)
{
	char *base;
	
	base = "0123456789ABCDEF";
	if (num <= 15 )
	{
		ft_putchar_fd(base[num], 1);
		(*len)++;	
	}
	else
	{
		ft_print_HEXAA(num / 16, len);
		ft_print_HEXAA(num % 16, len);
	}
}