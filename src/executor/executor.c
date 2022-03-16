/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/16 09:19:57 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		t_cmd *cmd = shell->cmds[0];

		if (cmd->name == "echo")
		{
			
		}
		if (cmd->name == "cd")
		{

		}
		if (cmd->name == "EXPORT" )
		{

		}
	}
}