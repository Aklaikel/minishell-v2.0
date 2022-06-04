/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:03:46 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/03 07:08:26 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int	get_nbr(const char *str)
{
	int		i;
	int		n;
	long	result;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			n = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (printf("exit: %s: numeric argument required\n", str), \
			clear(), exit(255), 255);
	return (result * n);
}

void	exit_cmd(char **cmd)
{
	int	status;

	if (!cmd || !*cmd || ft_strncmp(*cmd, "exit", 255))
		return ;
	if (!cmd[1])
	{
		clear();
		exit(0);
	}
	status = get_nbr(cmd[1]);
	if (cmd[2])
	{
		g_global.exit_status = 1;
		printf("minishell: exit: too many arguments\n");
	}
	else
	{
		clear();
		exit(status);
	}
}