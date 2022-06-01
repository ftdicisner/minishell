/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:39:46 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/31 20:49:23 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_digits_only(const char *s)
{
	while (*s)
	{
		if (ft_isdigit(*s++) == 0)
			return (1);
	}
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (cmd->n_args > 2)
		print_error("exit", TOO_MANY_ARGS, EXIT_FAILURE);
	if (cmd->n_args == 2)
	{
		if (is_digits_only(cmd->args[1]) == 1)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(cmd->args[1]);
	}
	else
		exit_code = 0;
	free_shell(shell);
	exit(exit_code);
	return (exit_code);
}
