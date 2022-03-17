/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:11:24 by jfrancis          #+#    #+#             */
/*   Updated: 2022/03/16 13:48:23 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_output(int i, t_cmd *cmd)
{
	int		arg_len;
	int		j;

	arg_len = ft_strlen(cmd->args[i]);
	j = 0;
	if (i >= 1)
		ft_putchar_fd(' ', 1);
	while (j <= arg_len)
	{
		if (cmd->args[i][j] != '\"' && cmd->args[i][j] != '\'')
			ft_putchar_fd(cmd->args[i][j], 1);
		j++;
	}
}

void	builtin_echo(t_cmd *cmd)
{
	char	*flag;
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 0;
	flag = "-n";
	while (i < cmd->n_args)
	{
		if (ft_strncmp(cmd->args[i], flag, 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		else
		{
			echo_output(i, cmd);
		}
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}
