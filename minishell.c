/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/03/20 21:01:40 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
	(void)ac;
	(void)av;
	(void)env;
	handle_signals();
	while(1);
}
