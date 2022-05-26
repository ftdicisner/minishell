/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:21:30 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/26 16:58:50 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_wronly_file(t_redir *redir)
{
	if (redir->mode == DOUBLE)
		return (open(redir->file, O_APPEND
				| O_WRONLY | O_CREAT, 0664));
	return (open(redir->file, O_TRUNC | O_WRONLY
			| O_CREAT, 0664));
}

int	ft_open_ronly_file(t_redir *redir)
{
	return (open(redir->file, O_RDONLY));
}
