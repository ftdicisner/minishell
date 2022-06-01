/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:29:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/06/01 17:33:55 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*command;

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

// Returns the full command path if exist
// Returns NULL if doesn't exist
char	*get_cmd(t_shell *shell, char *cmd)
{
	char	*command;
	char	**paths;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	paths = get_path_var(shell);
	if (paths == NULL)
		return (NULL);
	command = get_cmd_path(cmd, paths);
	free_array(paths);
	return (command);
}

int	ft_exec(char *cmd_name, char **cmd_args, t_shell *shell)
{
	int		status;
	char	**env_vars;

	env_vars = lst_env_to_strs(shell->env_vars);
	status = execve(cmd_name, cmd_args, env_vars);
	if (status != 0)
		perror("execve");
	free_array(env_vars);
	return (status);
}

int	default_exec(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_str;
	int		status;

	if (ft_strncmp("./", cmd->name, 2) == 0)
	{
		if (access(cmd->name + 2, 0) == 0)
			status = ft_exec(cmd->name + 2, cmd->args, shell);
		else
			status = print_error(cmd->name, COMMAND_NOT_FOUND, 127);
	}
	else
	{
		cmd_str = get_cmd(shell, cmd->name);
		if (cmd_str == NULL)
			status = print_error(cmd->name, COMMAND_NOT_FOUND, 127);
		else
			status = ft_exec(cmd_str, cmd->args, shell);
		free(cmd_str);
	}
	return (status);
}
