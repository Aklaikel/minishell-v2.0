/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:38:32 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/13 17:21:00 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putnbr_pf(int n,int *len, int fd)
{
	long int	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_pf('-', fd);
		(*len)++;
		i = -1 * i;
	}
	if (i <= 9)
	{
		ft_putchar_pf(i + 48, fd);
		(*len)++;
	}
	else
	{
		ft_putnbr_pf(i / 10, len, fd);
		ft_putnbr_pf(i % 10, len, fd);
	}
}
