/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:57:51 by osallak           #+#    #+#             */
/*   Updated: 2021/11/11 15:38:59 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

static int	check_existing(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		indx;
	int		l;
	char	*ptr;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	indx = 0;
	l = len;
	while (check_existing(set, s1[indx]) && indx < len)
		indx++;
	len--;
	while (check_existing(set, s1[len]) && len)
		len--;
	if (!(l - indx))
		return (ft_strdup(""));
	ptr = (char *)malloc(((len - indx) + 2) * sizeof(char));
	if (!ptr)
		return (0);
	l = 0;
	while (indx <= len)
		ptr[l++] = s1[indx++];
	ptr[l] = '\0';
	return (ptr);
}
