/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:46:19 by osallak           #+#    #+#             */
/*   Updated: 2021/11/18 18:08:47 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		dest = malloc(((ft_strlen(s) - start) + 1) * sizeof(char));
	else
		dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (s[start] && count < len)
		dest[count++] = s[start++];
	dest[count] = 0;
	return (dest);
}
