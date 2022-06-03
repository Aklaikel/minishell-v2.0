/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 06:07:30 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 07:27:25 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_venv(t_env *venv)
{
	while (venv)
	{
		printf("declare -x %s", venv->env_name);
		if (venv->env_value)
			printf("=\"%s\"", venv->env_value);
		printf("\n");
		venv = venv->next;
	}
}

void	export_cmd(char **cmd, t_env **venv)
{
    int i;

    if (!venv || !cmd \
		|| !*cmd || ft_strncmp(cmd[0], "export", 255))
		return ;
	if (!cmd[1])
		return (display_venv(*venv));
    i = 0;
    while(cmd[++i]);
}
