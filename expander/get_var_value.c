/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 07:29:59 by osallak           #+#    #+#             */
/*   Updated: 2022/06/01 09:20:25 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_varline(t_env  *env, char *varname)
{
    char    *varline;

    while (env)
    {
        if (ft_strnstr(env->))
        env = env->next;
    }
    return (varline);
}

char    *get_var_value(t_env *env, char *varname)
{
    char    *varline;
    char    *varvalue;

    varline = get_varline(env, varname);
    varvalue = ft_substr(varline, ft_strlen(varname) + 1, ft_strlen(varline));
    return (varvalue);
}
