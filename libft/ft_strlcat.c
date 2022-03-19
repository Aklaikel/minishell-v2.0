/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:37:02 by osallak           #+#    #+#             */
/*   Updated: 2021/11/18 18:16:28 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	l;
	int		res;

	res = (ft_strlen(src) + ft_strlen(dest));
	if (((n - 1) < ft_strlen(dest)) || !n)
		return (ft_strlen(src) + n);
	l = ft_strlen(dest);
	i = 0;
	while (l < n - 1 && src[i])
		dest[l++] = src[i++];
	dest[l] = '\0';
	return (res);
}
