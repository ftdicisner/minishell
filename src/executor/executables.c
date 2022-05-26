/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:29:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 13:15:24 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the full command path if exist
// Returns NULL if doesn't exist
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int	default_exec(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_str;
	int		status;

	cmd_str = get_cmd(shell->paths, cmd->name);
	if (cmd_str == NULL)
	{
		print_error(cmd->name, COMMAND_NOT_FOUND);
		status = EXIT_FAILURE;
	}
	else
	{
		status = execve(cmd_str, cmd->args, lst_env_to_strs(shell->env_vars));
	}
	return (status);
}
