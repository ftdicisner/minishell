/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:22:59 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/27 20:02:31 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_directory(void)
{
	return (getcwd(NULL, 0));
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = get_current_directory();
	if (cwd)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		free(cwd);
	}
}
