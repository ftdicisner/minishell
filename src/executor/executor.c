/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/23 11:44:41 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		t_cmd *cmd = shell->cmds[0];

		int pid = fork();

		if (pid == 0)
		{
			if (ft_strcmp(cmd->name, "echo") == 0)
				builtin_echo(cmd, shell);
			else if (ft_strcmp(cmd->name, "cd") == 0)
				builtin_cd(cmd, shell);
			else if (ft_strcmp(cmd->name, "pwd") == 0)
				builtin_pwd(cmd, shell);
			else if (ft_strcmp(cmd->name, "env") == 0)
				builtin_env(cmd, shell);
			else if (ft_strcmp(cmd->name, "export") == 0)
				builtin_export(cmd, shell);
			else if (ft_strcmp(cmd->name, "unset") == 0)
				builtin_unset(cmd, shell);
			else
				default_exec(cmd, shell);
		}
		else
			wait(NULL);
	}
}