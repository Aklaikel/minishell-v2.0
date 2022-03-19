/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:30:37 by osallak           #+#    #+#             */
/*   Updated: 2021/11/10 14:30:40 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

char	*ft_strdup(const char *src)
{
	int		len;
	char	*cpy;
	int		i;

	len = ft_strlen(src);
	if (!src)
		return (NULL);
	cpy = (char *)malloc(len + 1 * sizeof(char));
	if (!cpy)
		return (0);
	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = src[i];
	return (cpy);
}
