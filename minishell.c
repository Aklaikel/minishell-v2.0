/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/11 10:20:16 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_global	g_global;

void	print_version(char **av, int ac)
{
	(void)ac;
	if (!av || !av[1] || !*av[1])
		return ;
	if (!ft_strncmp(av[1], "--version", ft_strlen(av[1])))
	{
		ft_putstr_fd("minishell, version 2.0.0(1)-release (x86_64-apple-darwin18.7.0)\n", 1);
		ft_putstr_fd("Copyright (C) 2022 Oussama Sallak aka (uss4ma) && anass klaikel aka (9li9el)\n", 1);
		ft_putstr_fd("if you find an issue please be a man and tell us on this github repo:\n", 1);
		ft_putstr_fd("<<https://github.com/Aklaikel/minishell-v2.0/issues>>\n"\
			, 1);
		clear_exit(0);
	}
}

int	get_input(t_tokens **tokens)
{
	char	*input;
	int		status;

	status = 0;
	input = readline("minishell-v2.0$ ");
	if (!input)
	{
		write (1, "exit\n", 5);
		clear_exit(0);
	}
	add_history(input);
	*tokens = tokenizer(input);
	free(input);
	status = syntax_analyser(*tokens);
	if (status != 0)
	{
		set_status(status);
		return (status);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*tokens;
	t_env		*env_list;
	t_tree		*tree;

	tokens = NULL;
	handle_signals();
	env_list = get_env(env);
	print_version(av, ac);
	while (true)
	{
		if (get_input(&tokens) != 0)
			continue ;
		remove_quotes(&tokens);
		merge_words(&tokens);
		remove_spaces(&tokens);
		expander(get_env(env), &tokens);
		tree = parser(&tokens);
		g_global.is_runing = 1;
		run(tree, &env_list);
		g_global.is_runing = 0;
	}
	rl_clear_history();
	clear_exit(0);
}
