/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 05:40:35 by kalikel           #+#    #+#             */
/*   Updated: 2022/06/08 20:21:29 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	valid_newline(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (1);
	return (0);
}

static void	print_words(char **words, int *fd)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_putstr_fd(words[i++], fd[1]);
		if (words[i])
			ft_putstr_fd(" ", fd[1]);
	}
}

void	echo_cmd(char **cmd, int *fd)
{
	int		i;
	bool	is_set;

	if (!cmd || !*cmd || ft_strncmp(cmd[0], "echo", 255))
		return ;
	i = 1;
	is_set = true;
	while (cmd[i] && cmd[i][0] == '-')
	{
		if (!valid_newline(cmd[i]))
			is_set = false;
		else
			break ;
		i++;
	}
	print_words(&cmd[i], fd);
	if (is_set)
		ft_putstr_fd("\n", fd[1]);
}
