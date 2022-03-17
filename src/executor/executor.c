/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/16 12:34:10 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		t_cmd *cmd = shell->cmds[0];

		if (ft_strcmp(cmd->name, "echo") == 0)
			builtin_echo(cmd);
		if (ft_strcmp(cmd->name, "cd") == 0)
			builtin_cd(cmd);
		if (cmd->name == "EXPORT" )
		{

		}
	}
}