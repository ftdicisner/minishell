/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:30:25 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/31 20:56:39 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *cmd, char *error_msg, int err_status)
{
	printf("%s: %s\n", cmd, error_msg);
	return (err_status);
}

int	print_error_export(char *arg, int err_status)
{
	printf("export: `%s': not a valid identifier\n", arg);
	return (err_status);
}
