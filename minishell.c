/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 16:42:53 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_global	g_global;

void	sigquit_handler(int siq)
{
	(void)siq;
	// exit status must be 128 + sig like the bash but for now i use (0)
	// must clear the readline
	exit(0);
}

void	handle_signals(void)
{
	signal(SIGQUIT, &sigquit_handler);
	signal(SIGINT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tokens	*tokens;

	(void)ac;
	(void)av;
	(void)env;
	tokens = NULL;
	handle_signals();
	while (true)
	{
		input = (char *)collect(readline("minishell-v2.0$ "));
		add_history(input);
		tokens = tokenizer(input);
		syntax_analyser(tokens);
		printf("exit_status = : %d\n", g_global.exit_status);
		g_global.exit_status = 0;
	}
}
