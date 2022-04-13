/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:28:42 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/13 17:19:01 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hexa(unsigned long num, int *len)
{
	char *base;
	
	base = "0123456789abcdef";
	if (num <= 15 )
	{
		ft_putchar_pf(base[num], 1);
		(*len)++;	
	}
	else
	{
		ft_print_hexa(num / 16, len);
		ft_print_hexa(num % 16, len);
	}
}
