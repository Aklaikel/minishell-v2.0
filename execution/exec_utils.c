/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 00:25:57 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/11 00:44:19 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	get_status(int x)
{
	if (WIFEXITED(x))
		return (WEXITSTATUS(x));
	return (1);
}

void	handle_red(int *fd)
{
	dup2(fd[1], 1);
	if (fd[1] != 1)
		close(fd[1]);
	dup2(fd[0], 0);
	if (fd[0] != 0)
		close(fd[0]);
}

char	*append_char(char *str, char c)
{
	char	*add;
	int		len;

	if (!str)
	{
		add = malloc(2);
		add[0] = c;
		add[1] = 0;
		return (add);
	}
	len = ft_strlen(str);
	add = malloc(len + 2);
	ft_strlcpy(add, str, len + 1);
	add[len] = c;
	add[len + 1] = 0;
	return (add);
}

char	*get_path(char *word, t_env *env)
{
	char	**cmd;
	char	*path;
	char	*ret;
	int		i;

	ret = NULL;
	if (!word || !*word || !env)
		return (NULL);
	if (access(word, X_OK) == 0)
		return (word);
	path = find_env("PATH", env);
	cmd = (char **)collect(ft_split(path, ':'));
	i = -1;
	while (cmd[++i])
	{
		collect(cmd[i]);
		cmd[i] = collect(append_char(cmd[i], '/'));
		cmd[i] = collect(ft_strjoin(cmd[i], word));
		if (!ret && access(cmd[i], X_OK) == 0)
			ret = cmd[i];
	}
	return (ret);
}

char	**env_arr(t_env *env)
{
	char	**env_arr;
	int		i;
	t_env	*var;

	i = 0;
	var = env;
	while (var)
		var = (i++, var->next);
	env_arr = collect(malloc(sizeof(char *) * i));
	i = 0;
	while (env)
	{
		env_arr[i] = env->env_name;
		env_arr[i] = collect(append_char(env_arr[i], '='));
		env_arr[i] = collect(ft_strjoin(env_arr[i], env->env_value));
		i++;
		env = env->next;
	}
	return (env_arr[i] = NULL, env_arr);
}
