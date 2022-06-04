/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 07:29:59 by osallak           #+#    #+#             */
/*   Updated: 2022/06/03 08:52:59 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strstr(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	while (haystack[i] && haystack[i] != '=')
	{
		if (haystack[i] == needle[0])
		{
		    j = 0;
			l = i;
			while (needle[j] && (haystack[l] == needle[j]))
			{
				l++;
				if (!needle[++j])
					return (1);
			}			
		}
		i++;
	}
	return (0);
}

// char	*get_varline(t_env  *env, char *varname)
// {
// 	while (env)
// 	{
// 		if (ft_strstr(env->env_line, varname))
// 			return (env->env_line);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// char	*get_var_value(t_env *env, char *varname)
// {
// 	char	*varline;
// 	char	*varvalue;

// 	varline = get_varline(env, varname);
// 	if (!varline)
// 		return ((char *)collect(ft_strdup("")));
// 	varvalue = (char *)collect(ft_substr(varline, ft_strlen(varname) + 1, ft_strlen(varline)));
// 	return (varvalue);
// }
