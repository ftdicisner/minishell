/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:21:30 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/31 21:33:54 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_wronly_file(t_redir *redir)
{
	int	fd;

	if (redir->mode == DOUBLE)
		fd = open(redir->file, O_APPEND
				| O_WRONLY | O_CREAT, 0664);
	else
		fd = (open(redir->file, O_TRUNC | O_WRONLY
					| O_CREAT, 0664));
	if (fd > 0)
		return (fd);
	else
	{
		perror(redir->file);
		exit(EXIT_FAILURE);
	}
}

int	ft_open_ronly_file(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd > 0)
		return (fd);
	else
	{
		perror(redir->file);
		exit(EXIT_FAILURE);
	}
}
