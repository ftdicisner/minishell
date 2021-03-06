/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:26:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 20:49:49 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_pipe(int *fd)
{
	if (pipe(fd) == -1)
		print_error("exit", "Error while creating the pipe", EXIT_FAILURE);
	return (0);
}

void	init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;
	int		n;

	if (shell->n_cmds == 0)
	{
		shell->pipes = NULL;
		return ;
	}
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
		assign_pipe(pipes[i]);
		i++;
	}
	shell->pipes = pipes;
}

void	dup_pipes_cmd(t_shell *shell, t_cmd *cmd, int i)
{
	dup_pipes_in(shell, cmd, i);
	dup_pipes_out(shell, cmd, i);
}

void	close_pipes_cmd(t_shell *shell, int i)
{
	if (shell->n_cmds != 1)
	{
		if (i != 0)
			close(shell->pipes[i - 1][0]);
		if (i != shell->n_cmds - 1)
			close(shell->pipes[i][1]);
	}
}
