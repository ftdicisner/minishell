/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/07 10:01:32 by dicisner         ###   ########.fr       */
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

void	select_exec_cmd(t_cmd *cmd, t_shell *shell)
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

void	execute_child(t_cmd *cmd, t_shell *shell, int i)
{
	int pid;

	// Todo: Move the exit inside the execute_cmd	
	if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd, shell);
	pid = fork();
	if (pid == 0)
	{
		dup_pipes_cmd(shell, cmd, i);
		select_exec_cmd(cmd, shell);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close_pipes_cmd(shell, i);
}

// Test passed: "ls"
// Test passed: "ls | grep a"
// Test passed: "ls | grep a | grep out"
void	executor(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->n_cmds)
	{
		execute_child(shell->cmds[i], shell, i);
		i++;
	}
}