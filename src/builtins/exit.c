/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:39:46 by jfrancis          #+#    #+#             */
/*   Updated: 2022/04/26 20:37:43 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void destroy_shell(t_shell *shell)
{
	free(shell);
}

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->n_args > 1)
		print_error("exit", TOO_MANY_ARGS);
	destroy_shell(shell);
	exit(EXIT_SUCCESS);
}
