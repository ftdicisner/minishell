/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:08:41 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/21 11:37:49 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_splitted(char **s_arr)
{
	int	n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (1);
	else
		return (ft_strncmp(s1, s2, s1_len));
}

void	parse_env_var(int i, t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[i][ft_strlen(cmd->args[i]) - 1] != '\"')
		print_error(cmd->name, INVALID_INPUT);
	if (cmd->args[i][1] == '$')
		print_env_var_val(i, cmd, shell);
}

void	print_env_var_val(int i, t_cmd *cmd, t_shell *shell)
{
	t_var	*var;
	char	*path;

	path = ft_strtrim(cmd->args[i], "\" $");
	var = find_var(shell->env_vars, path);
	if (var)
		printf("%s", var->value);
	else
		printf("%c", 00);
}
