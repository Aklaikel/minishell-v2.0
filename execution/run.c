/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:10:34 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 07:14:58 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run(t_tree  *cmd)
{
    if(!cmd)
        return ;
    if (cmd->type == CMDLIST)
        return (run_cmdlist(cmd));
}