/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/27 20:07:23 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_cmd_status;

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->action = malloc(sizeof(t_sigaction));
	shell->env_vars = init_env(env);
	g_cmd_status = 0;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	t_shell	*shell;

	if (!argc && !argv)
		return (0);
	shell = init_shell(env);
	while (1)
	{
		config_signal(shell->action, &handle_sig, SIGINT);
		config_signal(shell->action, SIG_IGN, SIGQUIT);
		cmd_line = readline("\033[32mminishell~$\033[0m ");
		if (cmd_line == NULL)
		{
			printf("Exiting minihell...\n");
			free_shell(shell);
			exit(EXIT_SUCCESS);
		}
		add_history(cmd_line);
		parse_line(cmd_line, shell);
		init_pipes(shell);
		executor(shell);
		free_shell_tmp(shell);
		free(cmd_line);
	}
	return (EXIT_SUCCESS);
}
