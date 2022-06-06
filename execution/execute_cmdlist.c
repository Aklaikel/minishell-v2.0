/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:41:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/06 17:29:13 by osallak          ###   ########.fr       */
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

	if (!word || !*word || !env )
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
	while(var)
	{
		var = var->next;
		i++;
	}
	env_arr = malloc(sizeof(char *) * i);
	if(!env_arr)
		return (NULL);
	i = 0;
	while(env)
	{
		env_arr[i] = env->env_name;
		collect(append_char(env_arr[i], '='));
		collect(ft_strjoin(env_arr[i++], env->env_value));
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

// static bool	is_builtin(char *cmd, char **argv, char **env)
// {
// 	(void)env;
// 	if (!ft_strncmp(cmd, "echo", sizeof("echo") + 1))
// 		return (echo_cmd(argv), true);
// 	return true;
// }

void	execute_cmd(char *cmd, char **argv, t_env **env)                                                                                                                    
{
	int	pid;
	char **venv;

	// if(is_builtin(cmd, argv, env))
	// 	return ;
	cmd = get_path(cmd,*env);
	venv = env_arr(*env);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execve(cmd, argv, venv);
		ft_printf("minishell: %s: command not found\n", *argv);
		exit(1);
	}
	waitpid(pid, &g_global.exit_status, 0);
}
