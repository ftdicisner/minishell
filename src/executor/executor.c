/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:23:55 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/21 13:23:08 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		t_cmd *cmd = shell->cmds[0];

		if (ft_strcmp(cmd->name, "echo") == 0)
			builtin_echo(cmd, shell);
		if (ft_strcmp(cmd->name, "cd") == 0)
			builtin_cd(cmd, shell);
		if (ft_strcmp(cmd->name, "pwd") == 0)
			builtin_pwd(cmd, shell);
		if (ft_strcmp(cmd->name, "env") == 0)
			builtin_env(cmd, shell);
		if (ft_strcmp(cmd->name, "export") == 0)
			builtin_export(cmd, shell);
		if (ft_strcmp(cmd->name, "unset") == 0)
			builtin_unset(cmd, shell);
	}
}