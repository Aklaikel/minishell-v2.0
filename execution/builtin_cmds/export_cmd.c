/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 06:07:30 by aklaikel          #+#    #+#             */
/*   Updated: 2022/06/10 02:30:15 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_venv(t_env *venv)
{
	while (venv)
	{
		printf("declare -x %s", venv->env_name);
		if (venv->env_value)
			printf("=\"%s\"", venv->env_value);
		printf("\n");
		venv = venv->next;
	}
}

static bool	is_not_valid(char *line, int i)
{
	return ((line[i] == '+' && line[i + 1] != '=' && line[i]) \
		|| (line[0] != '_' && !ft_isalpha(line[0]))
		|| (line[i] != '=' && line[i] != '+' \
		&& !ft_isalnum(line[i]) && line[i]));
}

static void	append_to_env(char **tab, bool append, \
	t_env **v_env)
{
	t_env	*var;

	if (!v_env)
		return ;
	var = *v_env;
	while (var)
	{
		if (!ft_strncmp(var->env_name, tab[0], 255) \
			&& (var->env_value || tab[1]))
		{
			if (append && var->env_value)
				var->env_value = collect(ft_strjoin(var->env_value, tab[1]));
			else
				var->env_value = tab[1];
			return ;
		}
		var = var->next;
	}
	var = malloc(sizeof(t_env));
	var->env_name = tab[0];
	var->env_value = tab[1];
	var->next = NULL;
	add_back(v_env, var);
}

static int	append_var(char *line, t_env **env)
{
	char	*env_name;
	char	*env_value;
	char	*tab[2];
	int		i;

	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	if (is_not_valid(line, i))
	{
		g_global.exit_status = 1;
		return (printf("minishell: export: `%s': not a valid identifier\n", \
		line), -1);
	}
	env_name = collect(ft_substr(line, 0, i));
	if (line[i] == 0)
		env_value = NULL;
	else if (line[i] == '+')
		env_value = collect(ft_strdup(&line[i + 2]));
	else
		env_value = collect(ft_strdup(&line[i + 1]));
	tab[0] = env_name;
	tab[1] = env_value;
	return (append_to_env(tab, (line[i] == '+'), env), 0);
}

void	export_cmd(char **cmd, t_env **venv)
{
	int	i;

	if (!venv || !cmd \
		|| !*cmd || ft_strncmp(cmd[0], "export", 255))
		return ;
	if (!cmd[1])
		return (display_venv(*venv));
	if (cmd[1][0] == '-' \
		&& cmd[1][1] != '\0' && cmd[1][1] != '-')
	{
		g_global.exit_status = 1;
		printf("%s: illegal option -- %c\n", cmd[0], cmd[1][1]);
		printf("usage: export [with no options]\n");
		return ;
	}
	i = 0;
	while (cmd[++i])
		if (append_var(cmd[i], venv) == -1)
			return ;
}
