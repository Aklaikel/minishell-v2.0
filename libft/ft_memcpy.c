/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:06:08 by osallak           #+#    #+#             */
/*   Updated: 2021/11/10 14:42:34 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>

void	*ft_memcpy(void *des, const void *src, size_t n)
{
	size_t	i;

	if (!des && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((char *)(des + i)) = *((char *)(src + i));
		i++;
	}
	return (des);
}
