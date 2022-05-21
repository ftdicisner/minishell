/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:55:08 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/20 20:30:57 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*buffer;

	i = chdir(cmd->args[1]);
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
