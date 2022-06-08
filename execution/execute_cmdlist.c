/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:41:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/08 02:14:05 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*append_char(char *str, char c)
{
	char	*append;
	int		len;

	if (!str)
	{
		append = malloc(2);
		append[0] = c;
		append[1] = 0;
		return (append);
	}
	len = ft_strlen(str);
	append = malloc(len + 2);
	ft_strlcpy(append, str, len + 1);
	append[len] = c;
	append[len + 1] = 0;
	return (append);
}

char	*get_path(char *word, t_env *env)
{
	char	**cmd;
	char	*path;
	int		i;

	if (!word || !*word || !env)
		return (NULL);
	if (access(word, X_OK) == 0)
		return (word);
	path = find_env("PATH", env);
	cmd = ft_split(path, ':');
	if (!cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		collect(cmd[i]);
		cmd[i] = collect(append_char(cmd[i], '/'));
		cmd[i] = collect(ft_strjoin(cmd[i], word));
		if (access(cmd[i], X_OK) == 0)
			return (free(cmd), cmd[i]);
	}
	return (free(cmd), NULL);
}

char **env_arr(t_env *env)
{
	char	**env_arr;
	int 	i;
	t_env	*var;

	i = 0;
	var = env;
	while (var)
	{
		var = var->next;
		i++;
	}
	env_arr = malloc(sizeof(char *) * i);
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_arr[i] = env->env_name;
		env_arr[i] = collect(append_char(env_arr[i], '='));
		env_arr[i] = collect(ft_strjoin(env_arr[i], env->env_value));
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

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

static bool	is_builtin(char *cmd, char **argv, t_env **env)
{
	(void)env;
	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
		return (echo_cmd(argv), true);
	else if (!ft_strncmp(cmd, "cd", sizeof("cd") + 1))
		return (cd_cmd(argv, *env), true);
	else if (!ft_strncmp(cmd, "pwd", sizeof("pwd") + 1))
		return (pwd_cmd(argv), true);
	if (!ft_strncmp(cmd, "unset", sizeof("unset") + 1))
		return (unset_cmd(argv, env), true);
	if (!ft_strncmp(cmd, "env", sizeof("env") + 1))
		return (env_cmd(argv, *env), true);
	// if (!ft_strncmp(cmd, "export", sizeof("export") + 1))
	// 	return (export_cmd(argv, env), true);
	if (!ft_strncmp(cmd, "exit", sizeof("exit") + 1))
		return (exit_cmd(argv), true);
	return false;
}

int	get_status(int x)
{
	if (WIFEXITED(x))
		return (WEXITSTATUS(x));
	return (1);
}

void	execute_cmd(char *cmd, char **argv, t_env **env, int *fd)                                                                                                                    
{
	int	pid;
	char **venv;
	int tmp = 0;

	if(is_builtin(cmd, argv, env))
		return ;
	cmd = get_path(cmd,*env);
	venv = env_arr(*env);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		sigreset();
		dup2(fd[1], 1);
		if (fd[1] != 1)
			close(fd[1]);
		dup2(fd[0], 0);
		if (fd[0] != 0)
			close(fd[0]);
		execve(cmd, argv, venv);
		ft_printf("minishell: %s: command not found\n", argv[0]);
		exit(1);
	}
	waitpid(pid, &tmp, 0);
	g_global.exit_status = get_status(tmp);
}
