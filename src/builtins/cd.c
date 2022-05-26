/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:55:08 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/26 12:56:45 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *path, t_list *lst)
{
	if (ft_strcmp(path, "~") == 0)
		return (chdir(find_var(lst, "HOME")->value));
	return (chdir(path));
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*buffer;

	i = ft_chdir(cmd->args[1], shell->env_vars);
	buffer = NULL;
	if (cmd->n_args > 2)
	{
		printf("%s\n", TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	if (i == -1)
	{
		printf("%s\n", NO_SUCH_FILE);
		return (EXIT_FAILURE);
	}
	if (i == 0)
		export_var(shell->env_vars, "PWD", getcwd(buffer, 0));
	return (EXIT_SUCCESS);
}
