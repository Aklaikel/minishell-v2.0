/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:28:42 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/11 08:17:11 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hexal(unsigned long num, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (num <= 15)
	{
		ft_putchar_pf(base[num], 1);
		(*len)++;
	}
	else
	{
		ft_print_hexal(num / 16, len);
		ft_print_hexal(num % 16, len);
	}
}
