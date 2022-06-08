/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:10:34 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/08 20:17:15 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run_cmdlist(t_tree *cmd, t_env **env)
{
	int len = 0;
	t_cmdlist	*list;
	int fd[2];

	int i;
	list = cmd->cmdlist;
	while(cmd->cmdlist)
	{
		len++;
		cmd->cmdlist = cmd->cmdlist->next;
	}

	char	**cmdlist;

	cmdlist = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		cmdlist[i] = list->cmd;
		list = list->next;
		i++;
	}
	cmdlist[i] = NULL;
	if(cmd->errorflag)
	{
		printf("minishell: %s\n", strerror(cmd->errorflag));
		g_global.exit_status = 1;
		return ;
	}
	fd[0] = cmd->infd;
	fd[1] = cmd->outfd;
	if (!*cmdlist)
	{
		
		printf("minishell :command not found");
		g_global.exit_status = 1;
		return ;
	}
	execute_cmd(*cmdlist,cmdlist,env, fd);
}

void    run_and_or(t_tree *cmd, t_env **env)
{
	run(cmd->left, env);
	if ( ((cmd->type == OR) && (g_global.exit_status != 0))
		|| ((cmd->type == AND) && (g_global.exit_status == 0)) )
			run(cmd->right, env);
}

void	pipe_handler(t_tree	*cmd, t_env **env)
{
	int vfd[2];
	int pids[2];

	if (pipe(vfd) == -1)
		return ;
	pids[0] = fork();
	if(pids[0] == 0)
	{
		close(1);
		dup2(vfd[1], 1);
		close(vfd[1]);
		close(vfd[0]);
		run(cmd->left, env);
		exit(0);
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		close(0);
		dup2(vfd[0], 0);
		close(vfd[0]);
		close(vfd[1]);
		run(cmd->right, env);
		exit(0);
	} 
	close(vfd[0]);
    close(vfd[1]);
    waitpid(-1, &g_global.exit_status, 0);
    waitpid(-1, &g_global.exit_status, 0);
	return ;
}

void    run(t_tree  *cmd, t_env **env)
{
	if(!cmd)
		return ;
	if (cmd->type == CMDLIST)
		return (run_cmdlist(cmd, env));
	if (cmd->type == AND || cmd->type == OR)
		return(run_and_or(cmd, env));
	if (cmd->type == PIPE)
		return(pipe_handler(cmd,env));
}