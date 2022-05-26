/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:22:59 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/24 22:19:35 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_pwd(t_shell *shell)
{
	t_var	*pwd;

	pwd = find_var(shell->env_vars, "PWD");
	if (pwd)
		printf("%s\n", pwd->value);
	return (EXIT_SUCCESS);
}
