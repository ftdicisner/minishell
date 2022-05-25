/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:30:10 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/24 22:21:29 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->n_cmds - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	return (EXIT_SUCCESS);
}

void	free_redir_aux(void *redir)
{
	t_redir *redir_aux;

	redir_aux = (t_redir *)redir;
	free(redir_aux->file);
	free(redir_aux);
}


int		free_cmd_redir(t_cmd *cmd)
{
	ft_lstclear(&cmd->in_r, free_redir_aux);
	ft_lstclear(&cmd->out_r, free_redir_aux);
	return (EXIT_SUCCESS);
}

int		free_cmd_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->n_args)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	return (EXIT_SUCCESS);
}

int		free_cmd(t_cmd *cmd)
{
	free(cmd->name);
	free_cmd_args(cmd);
	free_cmd_redir(cmd);
	return (EXIT_SUCCESS);
}

int		free_cmds(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->n_cmds)
	{
		free_cmd(shell->cmds[i]);
		free(shell->cmds[i]);
		i++;
	}
	free(shell->cmds);
	return (EXIT_SUCCESS);
}

int		free_shell(t_shell *shell)
{
	free_cmds(shell);
	free_pipes(shell);
	return (EXIT_SUCCESS);
}



