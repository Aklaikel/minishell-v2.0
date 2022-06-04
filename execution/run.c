/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:10:34 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 21:00:58 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run_cmdlist(t_tree *cmd)
{
}
void    run(t_tree  *cmd)
{
    int i = 0;
    if(!cmd)
        return ;
    if (cmd->type == CMDLIST)
    {
        while (cmd->cmdlist && ++i)
            cmd->cmdlist = cmd->cmdlist->next;
    }
}