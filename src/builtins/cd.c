/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:55:08 by jfrancis          #+#    #+#             */
/*   Updated: 2022/03/16 13:46:33 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_cmd *cmd)
{
	int	i;

	i = chdir(cmd->args[0]);
	if (cmd->n_args > 1)
		printf("%s\n", TOO_MANY_ARGS);
	if (i == -1)
		printf("%s\n", NO_SUCH_FILE);
	return (i);
}
