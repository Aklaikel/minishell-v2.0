/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 05:44:03 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 06:49:38 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **cmd, t_env **env)
{
	int	i;

	if (!*env)
		return ;
	if (!cmd || !*cmd || ft_strncmp(cmd[0], "unset", 255))
		return ;
	if (cmd[1] && cmd[1][0] == '-' \
		&& cmd[1][1] != '\0' && cmd[1][1] != '-')
	{
		g_global.exit_status = 1;
		printf("%s: bad option: -%c\n", cmd[0], cmd[1][1]);
		return ;
	}
	i = 0;
	while (cmd[++i])
		find_remove_env(cmd[i], env);
}
