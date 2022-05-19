/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/19 16:36:32 by dicisner         ###   ########.fr       */
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

	shell = malloc(sizeof(shell));

	// move env variables to a linked list which contents are key-value
	shell->env_vars = init_env(env);
	shell->pipes = NULL;
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
	while (s = readline("minishell~ "))
	{
		// printf("%s\n", s);
		add_history(s);
		rl_redisplay();
		parse_line(s, shell);
		init_pipes(shell);
		executor(shell);
	}
	return (0);
}