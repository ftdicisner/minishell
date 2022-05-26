/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:42:58 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 13:33:12 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_var(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (ft_split(*envp + 5, ':'));
}
