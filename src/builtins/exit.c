/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:39:46 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/26 12:58:38 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroy_shell(t_shell *shell)
{
	free(shell);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->n_args > 1)
		print_error("exit", TOO_MANY_ARGS);
	destroy_shell(shell);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
