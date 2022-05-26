/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:22:31 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/25 21:25:47 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_shell_tmp(t_shell *shell)
{
	free_cmds(shell);
	free_pipes(shell);
	return (EXIT_SUCCESS);
}