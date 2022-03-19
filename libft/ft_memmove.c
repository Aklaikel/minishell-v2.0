/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:47:07 by osallak           #+#    #+#             */
/*   Updated: 2021/11/18 20:43:35 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest > src)
	{
		len--;
		while ((int)len >= 0)
		{
			*((char *)(dest + len)) = *((char *)(src + len));
			len--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
