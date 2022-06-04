/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:46:20 by osallak           #+#    #+#             */
/*   Updated: 2022/06/04 05:03:37 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_global	g_global;

// void	sigquit_handler(int siq)
// {
// 	(void)siq;
// 	// exit status must be 128 + sig like the bash but for now i use (0)
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	handle_signals(void)
{
	//signal(SIGINT, &sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	display_tree(t_tree *root, int level)
{
	if (root == NULL)
		return ;
	for (int i = 0; i < level; i++)
		printf(i == level -1 ? "|->" : "	");
	if (root->type == CMDLIST) printf("CMDLIST\n");
	else if (root->type == PIPE) printf("PIPE\n");
	else if (root->type == OR) printf("OR\n");
	else if (root->type == AND) printf("AND\n");
	display_tree(root->left, level + 1);
	display_tree(root->right, level + 1);
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
	while (true)
	{
		input = (char *)collect(readline("minishell-v2.0$ "));
		add_history(input);
		tokens = tokenizer(input);
		g_global.exit_status = 0;
		syntax_analyser(tokens);
		// remove_unwanted_tokens(&tokens);
		// printf("exit_status = : %d\n", g_global.exit_status);
		remove_quotes(&tokens);
		merge_words(&tokens);
		remove_spaces(&tokens);
		// display(tokens);
		// expander(get_env(env), tokens);
		if (g_global.exit_status == 0)
		{
			tree = parser(&tokens);
			run(tree, env);
			//display_tree(tree, 0);
		}
		// printf("%s\n", get_var_value(get_env(env), input));
		
	}
	rl_clear_history();
	clear_exit();
}
