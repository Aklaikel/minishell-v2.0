/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:51:36 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/11 09:20:57 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putnbr_u_fd(unsigned int n, int *len, int fd)
{
	unsigned int	i;

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
		ft_putnbr_u_fd(i / 10, len, fd);
		ft_putnbr_u_fd(i % 10, len, fd);
	}
}
