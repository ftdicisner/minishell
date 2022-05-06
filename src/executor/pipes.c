/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:26:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/05 22:08:50 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int assign_pipe(int *fd)
{
	if (pipe(fd) == -1)
		print_error("exit", "Error while creating the pipe");
	return (0);
}

void	init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;
	int		n;

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
	printf("Fueron creados %d pipes\n", n);
	shell->pipes = pipes;
}

void	dup_pipes_cmd(t_shell *shell, int i)
{

	int fd;

	if (shell->n_cmds)
	{
		if (i != 0 || shell->cmds[i]->in_r)
		{
			if (shell->cmds[i]->in_r)
			{
				fd = open(((t_redir *)(shell->cmds[i]->in_r->content))->file, O_RDONLY);
			}
			else
				fd = shell->pipes[i - 1][0];
			dup2(fd, 0);
			// close(shell->pipes[i - 1][1]);
			close(fd);
		}
		if (i != shell->n_cmds - 1)
		{

			// dup2(shell->pipes[i][1], 1);
			// close(shell->pipes[i][0]);
		}
	}
}

void	close_pipes_cmd(t_shell *shell, int i)
{

	if (shell->n_cmds != 1)
	{
		if (i != 0)
		{
			close(shell->pipes[i - 1][0]);
		}
		if (i != shell->n_cmds - 1)
			close(shell->pipes[i][1]);
	}

}