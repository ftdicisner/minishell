/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:26:24 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 16:55:49 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	free_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->n_cmds - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	return (EXIT_SUCCESS);
}
