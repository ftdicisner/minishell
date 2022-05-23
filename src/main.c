/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/22 22:00:17 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_status;

void	debug(t_shell *shell)
{
	debug_env_vars(shell->env_vars);
	export_var(shell->env_vars, "HELLO", "WORLD");

	debug_env_vars(shell->env_vars);

	export_var(shell->env_vars, "HELLO", "HELL");
	debug_env_vars(shell->env_vars);

	unset_var(shell->env_vars, "HELLO");
	debug_env_vars(shell->env_vars);

	unset_var(shell->env_vars, "NVM_BIN");
	debug_env_vars(shell->env_vars);

	t_var *var = find_var(shell->env_vars, "SHELL");
	printf("VAR FOUND: %s, %s\n", var->key, var->value);
}

t_shell	*init_shell(char** env)
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));

	shell->action = malloc(sizeof(t_sigaction));
	shell->env_vars = init_env(env);
	shell->paths = get_path_var(env);
	cmd_status = 0;
	// debug(shell);
	return (shell);
}


int	main(int argc, char **argv, char** env)
{
	char *s;
	t_shell *shell;

	ft_putstr_fd(env[0], 1);
	ft_putchar_fd('\n', 1);

	// REPL -> Read Evaluate Print Loop
	shell = init_shell(env);
	config_signal(shell->action, SIG_IGN, SIGQUIT);
	config_signal(shell->action, &handle_sig, SIGINT);
	while (s = readline("minishell~ "))
	{
		// printf("%s\n", s);
		add_history(s);
		rl_redisplay();
		parse_line(s, shell);

		// debug_quotes(s, shell);

		init_pipes(shell);
		executor(shell);
	}
	return (0);
}