/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:27:22 by osallak           #+#    #+#             */
/*   Updated: 2021/11/08 14:10:39 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ((unsigned char)c))
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == ((unsigned char)c))
		return ((char *)(s + i));
	return (0);
}
