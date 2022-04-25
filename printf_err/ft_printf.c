/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 00:58:23 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/22 09:34:08 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

//pf stands for printf
void	print_it(char c, va_list ptr, int *len)
{
	if (c == '%')
		(*len) += ft_putchar_pf('%', 1);
	else if (c == 'c')
		(*len) += ft_putchar_pf(va_arg(ptr, int), 1);
	else if (c == 's')
		(*len) += ft_printstr(va_arg(ptr, char *));
	else if (c == 'd' || c == 'i')
		ft_putnbr_pf(va_arg(ptr, int), len, 1);
	else if (c == 'u')
		ft_putnbr_u_fd(va_arg(ptr, unsigned int), len, 1);
	else if (c == 'x')
		ft_print_hexa(va_arg(ptr, unsigned int), len);
	else if (c == 'X')
		ft_print_HEXAA(va_arg(ptr, unsigned int), len);
	else if (c == 'p')
	{
		ft_putstr_pf("0x", 1);
		(*len)+= 2;
		ft_print_hexa(va_arg(ptr, unsigned long), len);
	}
}

int	ft_printf(const char *f, ...)
{
	int len;
	va_list	ptr;
	int	i;

	len = 0;
	i = 0;
	va_start(ptr, f);
	while (f[i])
	{
		if (f[i] == '%')
			print_it(f[++i], ptr, &len);
		else
		{
			ft_putchar_pf(f[i],1);
			len++;
		}
		i++;
	}
	va_end(ptr);
	return (len);
}
// #include<stdio.h>
// int main ()
// {
// 	int p1 = ft_printf("%X\n", 2002);
// 	int	p2 = printf("%X\n",2002);
//  	printf("%d == %d\n",p1, p2);
//  }
