/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/27 20:00:09 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (builtin_pwd(shell));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (builtin_env(cmd, shell));
	if (ft_strcmp(cmd->name, "export") == 0)
		return (builtin_export(cmd, shell));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd, shell);
	return (default_exec(cmd, shell));
}

void	execute_child(t_cmd *cmd, t_shell *shell, int i)
{
	int	pid;
	int	child_exit_status;
	int	status;

	config_signal(shell->action, &handle_sig_ignore, SIGINT);
	pid = fork();
	if (pid == 0)
	{
		config_signal(shell->action, &handle_sig_child, SIGINT);
		dup_pipes_cmd(shell, cmd, i);
		child_exit_status = select_exec_cmd(cmd, shell);
		exit(child_exit_status);
	}
	if (waitpid(pid, &status, 0) == -1)
		g_cmd_status = EXIT_FAILURE;
	if (WIFEXITED(status))
		g_cmd_status = WEXITSTATUS(status);
	close_pipes_cmd(shell, i);
}

static int	check_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	return (0);
}

// Test passed: "ls"
// Test passed: "ls | grep a"
// Test passed: "ls | grep a | grep out"
void	executor(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->n_cmds == 1 && check_builtin(shell->cmds[i]) == 1)
		g_cmd_status = select_exec_cmd(shell->cmds[i], shell);
	else
	{
		while (i < shell->n_cmds)
		{
			execute_child(shell->cmds[i], shell, i);
			i++;
		}
	}
}
