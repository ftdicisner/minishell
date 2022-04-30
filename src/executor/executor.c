/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/04/29 19:37:47 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterar en cada comando generando un child process
// En el parent

void	execute_cmd(t_cmd *cmd, t_shell *shell)
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

void	close_pipes(int **pipes, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_child(t_cmd *cmd, t_shell *shell, int i)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd, shell);

	int pid = fork();
	int **pipes = shell->pipes;
	int redir = 0;

	if (pid == 0)
	{
		if (i == 0)
		{  
			dup2(pipes[i + 1][1], 1);
          	if (redir)
            	dup2(pipes[i][0], 0); 
		}
		else if (i < shell->n_cmds - 1)
		{
			dup2(pipes[i][0], 0);
			dup2(pipes[i + 1][1], 1);
		}
		else
		{
			dup2(pipes[i][0], 0);
			dup2(pipes[shell->n_cmds][1], 1);
		}
		close_pipes(pipes, shell->n_cmds);
		execute_cmd(cmd, shell);
		exit(0);
	}
}

void	executor(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->n_cmds)
	{
		execute_child(shell->cmds[i], shell, i);
		i++;
	}
	close_pipes(shell->pipes, shell->n_cmds);
		
	int bsize = 256;
	char buf[bsize+1];
	ssize_t n = 0;
	while ((n = read(shell->pipes[shell->n_cmds][0], buf, bsize)) > 0) {
		buf[n] = '\0';
		write(1, buf, n);
	}
	close(shell->pipes[n][0]);
	wait(NULL);
}