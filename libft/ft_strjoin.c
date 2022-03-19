/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:09:52 by osallak           #+#    #+#             */
/*   Updated: 2021/11/18 20:43:55 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	count;
	size_t	tmp;
	char	*res;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	count = 0;
	while (count < ft_strlen(s1))
	{
		res[count] = s1[count];
		count++;
	}
	tmp = 0;
	while (count < len)
		res[count++] = s2[tmp++];
	res[count] = '\0';
	return (res);
}
