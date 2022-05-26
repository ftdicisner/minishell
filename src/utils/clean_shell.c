/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:22:31 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 16:07:59 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_shell_tmp(t_shell *shell)
{
	free_cmds(shell);
	free_pipes(shell);
	return (EXIT_SUCCESS);
}

void	free_tvar(void *tvar)
{
	t_var *var;

	var = (t_var *)tvar;
	free(var->key);
	free(var->value);
	free(var);
}

int		free_shell(t_shell *shell)
{
	ft_lstclear(&shell->env_vars, free_tvar);
	free_array(shell->paths);
	free(shell->action);
	return (EXIT_SUCCESS);
}
