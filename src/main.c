/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/04/30 18:53:46 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_shell	*init(char** env)
{
	t_shell *shell;

	shell = malloc(sizeof(shell));

	// move env variables to a linked list which contents are key-value
	shell->env_vars = init_env(env);
	shell->paths = get_path_var(env);
	// debug(shell);
	return (shell);
}

int ft_pipe(int *fd)
{
	pipe(fd);
	return (0);
}

void	init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;
	int		n;

	n = shell->n_cmds - 1;
	pipes = malloc(sizeof (int *) * n);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof (int) * 2);
		i++;
	}
	i = 0;
	while (i < n)
	{
		ft_pipe(pipes[i]);
		i++;
	}
	printf("Fueron creados %d pipes\n", n);
	shell->pipes = pipes;
}

int	main(int argc, char **argv, char** env)
{
	char *s;
	t_shell *shell;

	ft_putstr_fd(env[0], 1);
	ft_putchar_fd('\n', 1);

	// REPL -> Read Evaluate Print Loop
	shell = init(env);
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