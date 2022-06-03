/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 05:28:55 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 06:48:26 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_cmd(char **cmd, t_env *venv)
{
	t_env	*var;

	if (!cmd || !*cmd || ft_strncmp(*cmd, "env", 255))
		return ;
	if (cmd[1])
	{
		g_global.exit_status = 1;
		if (cmd[1][0] == '-' \
			&& cmd[1][1] != '\0' && cmd[1][1] != '-')
			err_printf("%s: illegal option -- %c\n", cmd[0], \
				cmd[1][1]);
		err_printf("usage: env [with no options] [with no arguments]\n");
		return ;
	}
    var = venv;
	while (var != NULL)
	{
		if (var->env_value != NULL)
		{
			ft_putstr_fd(var->env_name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(var->env_value, 1);
		}
		var = var->next;
	}
    
}

