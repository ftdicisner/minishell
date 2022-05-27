/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:42:58 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/27 17:10:32 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_var(t_shell *shell)
{
	t_var	*envp;

	envp = find_var(shell->env_vars, "PATH");
	if (envp == NULL)
		return (NULL);
	return (ft_split(envp->value, ':'));
}
