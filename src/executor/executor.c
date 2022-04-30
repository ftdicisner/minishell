/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/04/30 18:46:11 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read(int fd)
{
	int bsize = 256;
	char buf[bsize+1];
	ssize_t n = 0;
	while ((n = read(fd, buf, bsize)) > 0) {
		buf[n] = '\0';
		write(1, buf, n);
	}
}

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
	while (i < n + 1)
	{
		// printf("Closing pipes %i\n", i);
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
		if (i == 0 && shell->n_cmds != 1)
		{  
			dup2(pipes[i + 1][1], 1);
			close(pipes[i][0]);
          	// if (FileIn)
            // 	dup2(FileIn, 0); 
		}
		else if (i < shell->n_cmds - 1)
		{
			dup2(pipes[i][0], 0);
			dup2(pipes[i + 1][1], 1);
			close(pipes[i][0]);
		}
		else
		{
			dup2(pipes[i][0], 0);
			close(pipes[i][0]);
			// if (fileOut)
			// 	dup2(fileoutPipe, 1);
		}
		// if (i == 1)
			// ft_read(pipes[1][0]);
		close_pipes(pipes, shell->n_cmds);
		execute_cmd(cmd, shell);
		exit(0);
	}
	// close_pipes(shell->pipes, shell->n_cmds);
	waitpid(pid, NULL, 0);
	close(pipes[i + 1][1]);
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
	// dup2(shell->pipes[shell->n_cmds][0], 0);
	close_pipes(shell->pipes, shell->n_cmds);
	// ft_read(0);
}