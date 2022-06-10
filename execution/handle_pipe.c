/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 00:15:44 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/10 07:10:32 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	rpipe(int *vfd, t_tree *cmd, t_env **env)
{
	close(0);
	dup2(vfd[0], 0);
	close(vfd[0]);
	close(vfd[1]);
	run(cmd->right, env);
}

static void	lpipe(int *vfd, t_tree *cmd, t_env **env)
{
	close(0);
	dup2(vfd[1], 1);
	close(vfd[0]);
	close(vfd[1]);
	run(cmd->left, env);
}

void	pipe_handler(t_tree	*cmd, t_env **env)
{
	int	vfd[2];
	int	pids[2];

	if (pipe(vfd) == -1)
		return ;
	pids[0] = fork();
	if (pids[0] == 0)
	{
		lpipe(vfd, cmd, env);
		exit(0);
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		rpipe(vfd, cmd, env);
		exit(0);
	}
	close(vfd[0]);
	close(vfd[1]);
	waitpid(-1, &g_global.exit_status, 0);
	waitpid(-1, &g_global.exit_status, 0);
	return ;
}
