/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:59:56 by osallak           #+#    #+#             */
/*   Updated: 2022/06/03 06:44:10 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *find, t_env *venv)
{
	int		i;
	t_env	*var;

	var = venv;
	while (var)
	{
		i = ft_strlen(var->env_name);
		if ((int) ft_strlen(find) > i)
			i = ft_strlen(find);
		if (!ft_strncmp(var->env_name, find, i))
			return (var->env_value);
		var = var->next;
	}
	return (NULL);
}

void	find_remove_env(char *find, t_env **venv)
{
	t_env	*var;

	var = *venv;
	if (!ft_strncmp(find, var->env_name, 255))
	{
		*venv = var->next;
		return ;
	}
	while (var)
	{
		if (var->next && !ft_strncmp(find, var->next->env_name, 255))
			var->next = var->next->next;
		var = var->next;
	}
}

t_env	*get_env(char **env)
{
	t_env	*head;
	int		i;

	i = -1;
	head = NULL;
	while (env[++i])
		add_back_env(&head, add_new_env(env[i]));
	return (head);
}
