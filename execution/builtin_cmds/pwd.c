/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 04:58:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 06:49:09 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(char **cmd)
{
	char	cwd[1024];

	if (!cmd || !*cmd || ft_strncmp(cmd[0], "pwd", 255))
		return ;
	if (cmd[1] && cmd[1][0] == '-' \
		&& cmd[1][1] != '\0' && cmd[1][1] != '-')
	{
		g_global.exit_status = 1;
		printf("%s: illegal option -- %c\n", cmd[0], cmd[1][1]);
		printf("usage: env [with no options]\n");
		return ;
	}
	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
	else
		perror("pwd:");
}
