/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/08 19:11:45 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_global	g_global;

void	sigquit_handler(int siq)
{
	(void)siq;
	if (g_global.is_runing)
		return ;
	// exit status must be 128 + sig like the bash but for now i use (0)
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, &sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigreset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	print_version(char **av)
{
	if (!av || !av[1] || !*av[1])
		return ;
	if (!ft_strncmp(av[1], "--version", ft_strlen(av[1])))
	{
		ft_putstr_fd("minishell, version 2.0.0(1)-release (x86_64-apple-darwin18.7.0)\n", 1);
		ft_putstr_fd("Copyright (C) 2022 Oussama Sallak aka (uss4ma) && anass klaikel aka (9li9el)\n", 1);
		ft_putstr_fd("if you find an issue please be a man and tell us on this github repo:\n", 1);
		ft_putstr_fd("<<https://github.com/Aklaikel/minishell-v2.0/issues>>\n", 1);
		clear_exit(0);
	}
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tokens	*tokens;
	t_env		*env_list;
	t_tree		*tree;

	(void)ac;
	(void)av;
	tokens = NULL;
	handle_signals();
	env_list = get_env(env);
	// for (t_env *head = env_list; head; head = head->next) {
	// 	printf("%s=%s\n", head->env_name, head->env_value);
	// }
	print_version(av);
	while (true)
	{
		input = readline("minishell-v2.0$ ");
		if (!input || !ft_strncmp("exit", input, 4))
		{
			write (1, "exit\n", 5);
			clear_exit(255);
		}
		add_history(input);
		tokens = tokenizer(input);
		syntax_analyser(tokens);
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
