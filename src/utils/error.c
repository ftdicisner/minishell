/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:30:25 by jfrancis          #+#    #+#             */
/*   Updated: 2022/03/21 10:52:04 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *error_msg)
{
	ft_putstr_fd(cmd, 2);
	write(2, ": ", 2);
	ft_putstr_fd(error_msg, 2);
}
