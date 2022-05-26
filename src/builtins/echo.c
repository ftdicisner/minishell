/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:11:24 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/26 12:57:02 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_output(int i, t_cmd *cmd)
{
	int		arg_len;
	int		j;

	arg_len = ft_strlen(cmd->args[i]);
	j = 0;
	if (i > 1)
		printf(" ");
	while (j < arg_len)
	{
		if (cmd->args[i][j] != '\"' && cmd->args[i][j] != '\'')
			printf("%c", cmd->args[i][j]);
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
int	builtin_echo(t_cmd *cmd)
{
	char	*flag;
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	flag = "-n";
	while (i < cmd->n_args)
	{
		if (ft_strncmp(cmd->args[i], flag, 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		else
			echo_output(i, cmd);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
