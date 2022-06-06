/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:10:34 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/06 09:15:34 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run_cmdlist(t_tree *cmd, t_env **env)
{
    int len = 0;
	t_cmdlist	*list;
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
   execute_cmd(*cmdlist,cmdlist,env);
}

void    run(t_tree  *cmd, t_env **env)
{
    if(!cmd)
        return ;
    if (cmd->type == CMDLIST)
        return (run_cmdlist(cmd, env));
    if (cmd->type == AND || cmd->type == OR)
        return(run_and_or(cmd, env));
}