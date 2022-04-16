/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/04/16 12:47:17 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		t_cmd *cmd = shell->cmds[0];
		int fd[2];


		if (pipe(fd) == -1)
			printf("Error al crear el pipe");

		int pid = fork();

		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
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
			else if (ft_strcmp(cmd->name, "exit") == 0)
				builtin_exit(cmd, shell);
			else
				default_exec(cmd, shell);
		}
		else
		{
			dup2(fd[0], 0);
			int bsize = 256;
			char buf[bsize+1];
			ssize_t n = 0;
			while ((n = read(fd[0], buf, bsize)) > 0) {
				buf[n] = '\0';
				write(1, buf, n);
			}
			close(fd[1]);
			close(fd[0]);
			wait(NULL);
		}
	}
}