/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 12:55:03 by dicisner         ###   ########.fr       */
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
	shell->paths = get_path_var(env);
	g_cmd_status = 0;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	char	*s;
	t_shell	*shell;

	if (!argc && !argv)
		return (0);
	shell = init_shell(env);
	config_signal(shell->action, SIG_IGN, SIGQUIT);
	config_signal(shell->action, &handle_sig, SIGINT);
	while (1)
	{
		s = readline("minishell~ ");
		add_history(s);
		rl_redisplay();
		parse_line(s, shell);
		init_pipes(shell);
		executor(shell);
		free_shell_tmp(shell);
	}
	return (EXIT_SUCCESS);
}
