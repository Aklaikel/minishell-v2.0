/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/03/30 17:17:21 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_gc *g_garbage = NULL;

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
	char	*input;

	(void)ac;
	(void)av;
	(void)env;
	handle_signals();
	while (true)
	{
		input = collect(readline("minishell-2.0$ "));
		add_history(input);
		tokenizer(input);
	}
}

//The readline() function can cause memory leaks. You don’t have to fix them. 