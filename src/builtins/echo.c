/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:11:24 by jfrancis          #+#    #+#             */
/*   Updated: 2022/03/21 11:37:43 by jfrancis         ###   ########.fr       */
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

/* Tests to pass:
	echo "string within double quotation marks"
	echo 'string within single quotation marks'
	echo "$ENV_VAR"
	echo '$ENV_VAR'
	echo string sem aspas
	echo
*/
void	builtin_echo(t_cmd *cmd, t_shell *shell)
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
			if (cmd->args[i][0] == '\"')
				parse_env_var(i, cmd, shell);
			else
				echo_output(i, cmd);
		}
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}
