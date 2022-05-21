/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/21 20:00:53 by jfrancis         ###   ########.fr       */
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

int		select_exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (builtin_echo(cmd, shell));
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (builtin_pwd(cmd, shell));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (builtin_env(cmd, shell));
	if (ft_strcmp(cmd->name, "export") == 0)
		return (builtin_export(cmd, shell));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (builtin_unset(cmd, shell));
	return (default_exec(cmd, shell));
}

void	execute_child(t_cmd *cmd, t_shell *shell, int i)
{
	int pid;
	int	child_exit_status;
	int status;

	// Todo: Move the exit inside the execute_cmd
	if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd, shell);
	pid = fork();
	if (pid == 0)
	{
		dup_pipes_cmd(shell, cmd, i);
		child_exit_status = select_exec_cmd(cmd, shell);
		exit(child_exit_status);
	}
    if (waitpid(pid, &status, 0) == -1 ) {
        cmd_status = EXIT_FAILURE;
    }
	if (WIFEXITED(status)) {
        cmd_status = WEXITSTATUS(status);
    }
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