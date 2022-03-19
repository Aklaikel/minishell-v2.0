/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:15:58 by osallak           #+#    #+#             */
/*   Updated: 2021/11/18 18:25:02 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	while (n)
	{
		count += 1;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;
	int		tmp;

	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = count_digits(n);
	tmp = 0;
	ptr = (char *) malloc((count + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[tmp++] = '-';
		n *= -1;
	}
	ptr[count] = 0;
	while (--count >= tmp)
	{
		ptr[count] = (n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}
