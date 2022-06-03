/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 03:08:43 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 06:37:34 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_error(char **cmd)
{
	g_global.exit_status = 1;
	printf("%s: illegal option -- %c\n", cmd[0], cmd[1][1]);
	printf("usage: cd [with no options]\n");
	return ;
}

static void	ft_error_home(void)
{
	g_global.exit_status = 1;
	printf("minishell: cd: HOME not set");
}

static int	change_dir(char *path)
{
	char	str[1024];

	if (!ft_strncmp(path, ".", 255) && !getcwd(str, 1024))
		perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
	return (chdir(path));
}

void	cd_cmd(char **cmd, t_env *env)
{
	int		i;
	char	*path;

	if (!cmd || !*cmd || ft_strncmp(cmd[0], "cd", 255))
		return ;
	if (cmd[1] && cmd[1][0] == '-' \
			&& cmd[1][1] != '\0' && cmd[1][1] != '-')
		ft_error(cmd);
	if (!cmd[1])
	{
		path = find_env("HOME", env);
		if (!path)
			ft_error_home();
		i = chdir(path);
	}
	else
		i = change_dir(cmd[1]);
	if (i < 0)
	{
		perror("cd");
		g_global.exit_status = 1;
	}
}