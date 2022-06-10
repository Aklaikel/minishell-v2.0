/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:10:34 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/10 04:54:52 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**len_cmdlist(t_tree *cmd)
{
	int			len;
	int			i;
	char		**cmdlist;
	t_cmdlist	*list;

	len = 0;
	list = cmd->cmdlist;
	while (cmd->cmdlist)
	{
		len++;
		cmd->cmdlist = cmd->cmdlist->next;
	}
	cmdlist = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		cmdlist[i] = list->cmd;
		list = list->next;
		i++;
	}
	cmdlist[i] = NULL;
	return (cmdlist);
}

void	run_cmdlist(t_tree *cmd, t_env **env)
{
	int			fd[2];
	char		**cmdlist;

	cmdlist = len_cmdlist(cmd);
	if (cmd->errorflag)
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
		clear_exit(127);
		return ;
	}
	execute_cmd(*cmdlist, cmdlist, env, fd);
}

void	run_and_or(t_tree *cmd, t_env **env)
{
	run(cmd->left, env);
	if (((cmd->type == OR) && (g_global.exit_status != 0)) \
		|| ((cmd->type == AND) && (g_global.exit_status == 0)))
		run(cmd->right, env);
}

void	run(t_tree *cmd, t_env **env)
{
	if (!cmd)
		return ;
	if (cmd->type == CMDLIST)
		return (run_cmdlist(cmd, env));
	if (cmd->type == AND || cmd->type == OR)
		return (run_and_or(cmd, env));
	if (cmd->type == PIPE)
		return (pipe_handler(cmd, env));
}
