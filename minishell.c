/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/16 07:54:46 by aklaikel         ###   ########.fr       */
=======
/*   Updated: 2022/04/25 12:03:34 by osallak          ###   ########.fr       */
>>>>>>> f3c017e96a348ed34e4819638b37da109890b1b3
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_global	g_global;

void	sigquit_handler(int siq)
{
	(void)siq;
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
		// check_and_or_pipe_bg(tokens);
		printf("exit_status = : %d\n", g_global.exit_status);
		g_global.exit_status = 0;
	}
	rl_clear_history();
}
