/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_HEXAA.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:39:16 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/11 08:16:50 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hexa(unsigned long num, int *len)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (num <= 15)
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
