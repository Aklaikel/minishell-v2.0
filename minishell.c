/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/04/16 07:54:46 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_gc *g_garbage = NULL;

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
		while (tokens)
		{
			if (tokens->flag == PIPE)
				printf("PIPE : ");
			else if (tokens->flag == WORD)
				printf("WORD : ");
			else if (tokens->flag == OUTRED)
				printf("OUTRED : ");
			else if (tokens->flag == INRED)
				printf("INRED : ");
			else if (tokens->flag == APPEND)
				printf("APPEND : ");
			else if (tokens->flag == HERDOC)
				printf("HERDOC : ");
			else if (tokens->flag == AND)
				printf("AND : ");
			else if (tokens->flag == OR)
				printf("OR : ");
			else if (tokens->flag == SPACE)
				printf("SPACE : ");
			else if (tokens->flag == OBRACKET)
				printf("OBRACKET : ");
			else if (tokens->flag == CBRACKET)
				printf("CBRACKET : ");
			else if (tokens->flag == SQUOTE)
				printf("SQUOTE : ");
			else if (tokens->flag == DQUOTE)
				printf("DQUOTE : ");
			else if (tokens->flag == BG)
				printf("BG : ");
			else if (tokens->flag == VAR)
				printf("VAR : ");
			printf("%s\n", tokens->token);
			tokens = tokens->next;
		}
	}
	rl_clear_history();
}
