/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:41:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/04 05:59:16 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/**
 	* The buitlin commands :
	*	- echo		-> Write arguments to the standard output.
	*	- cd 		-> Change the shell working directory.
	*	- pwd 		-> Print the name of the current working directory.
	*	- export 	-> Set export attribute for shell variables.
	*	- unset 	-> Unset values and attributes of shell variables.
	*	- env 		-> Set environment and execute command, or print environment.
	*	- exit		-> Exit the shell.
**/

// static bool	is_builtin(char *cmd, char **argv, char **env)
// {
// 	(void)env;
// 	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
// 		return (echo_cmd(argv), true);
// 	return true;
// }

void	execute_cmd(char *cmd, char **argv, char **env)
{
	int	pid;

	// if (is_builtin(cmd, argv, env))
	// 	return ;
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		(void) env;
		execvp(cmd, argv);
		ft_printf("minishell: %s: command not found\n", cmd);
		exit(1);
	}
	waitpid(pid, &g_global.exit_status, 0);
}
