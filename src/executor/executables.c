/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:29:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/22 10:00:29 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. Prueba concatenando el comando con cada path del ambiente
	2. Verifica si alguno de los comando+path existe en el sistema
	3. Si no existe ninguno bot "COmmand not found"
	4. Si existe, la pasamso a execve
*/

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;

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

void	default_exec(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_str;

	cmd_str = get_cmd(shell->paths, cmd->name);
	if (cmd_str == NULL)
		print_error(cmd->name, COMMAND_NOT_FOUND);
	else
		execve(cmd_str, cmd->args, lst_env_to_strs(shell->env_vars));
}