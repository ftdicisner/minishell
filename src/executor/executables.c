/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:29:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 21:36:44 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the full command path if exist
// Returns NULL if doesn't exist
char	*get_cmd(t_shell *shell, char *cmd)
{
	char	*tmp;
	char	*command;
	char	**paths;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	paths = get_path_var(shell);
	if (paths == NULL)
		return (NULL);
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

	cmd_str = get_cmd(shell, cmd->name);
	if (cmd_str == NULL)
	{
		print_error(cmd->name, COMMAND_NOT_FOUND, EXIT_FAILURE);
		status = 127;
	}
	else
	{
		printf("%s\n", cmd_str);
		status = execve(cmd_str, cmd->args, lst_env_to_strs(shell->env_vars));
	}
	free(cmd_str);
	return (status);
}
