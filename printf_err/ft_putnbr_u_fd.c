/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uss4ma <uss4ma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:51:36 by aklaikel          #+#    #+#             */
/*   Updated: 2022/08/04 19:10:00 by uss4ma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putnbr_u_fd(unsigned int n, int *len, int fd)
{
	unsigned int	i;

	i = n;
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
