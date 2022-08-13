/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uss4ma <uss4ma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:41:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/08/13 02:11:35 by uss4ma           ###   ########.fr       */
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

static bool	is_builtin(char *cmd, char **argv, t_env **env, int *fd)
{
	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
		return (echo_cmd(argv, fd), set_status(0), true);
	else if (!ft_strncmp(cmd, "cd", sizeof("cd") + 1))
		return (cd_cmd(argv, *env), set_status(0), true);
	else if (!ft_strncmp(cmd, "pwd", sizeof("pwd") + 1))
		return (pwd_cmd(argv, fd), set_status(0), true);
	if (!ft_strncmp(cmd, "unset", sizeof("unset") + 1))
		return (unset_cmd(argv, env), set_status(0), true);
	if (!ft_strncmp(cmd, "env", sizeof("env") + 1))
		return (env_cmd(argv, *env), set_status(0), true);
	if (!ft_strncmp(cmd, "export", sizeof("export") + 1))
		return (export_cmd(argv, env), set_status(0), true);
	if (!ft_strncmp(cmd, "exit", sizeof("exit") + 1))
		return (exit_cmd(argv), set_status(0), true);
	if (!ft_strncmp(cmd, "version", sizeof("exit") + 1))
		return (display_version(NULL, 2));
	return (false);
}

void	execute_cmd(char *cmd, char **argv, \
		t_env **env, int *fd)
{
	int		pid;
	char	**venv;
	int		tmp;

	tmp = 0;
	if (is_builtin(cmd, argv, env, fd))
		return ;
	cmd = get_path(cmd,*env);
	venv = env_arr(*env);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		sigreset();
		handle_red(fd);
		execve(cmd, argv, venv);
		ft_printf("minishell: %s: command not found\n", argv[0]);
		clear_exit(127);
	}
	waitpid(pid, &tmp, 0);
	g_global.exit_status = get_status(tmp);
}
