/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:08:41 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 11:35:52 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (1);
	else
		return (ft_strncmp(s1, s2, s1_len));
}

char	**lststr_to_arr(t_list *lst)
{
	int		i;
	int		size;
	char	**output;

	size = ft_lstsize(lst);
	output = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		output[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	output[i] = 0;
	return (output);
}

char	**lststr_to_token_arr(t_list *lst)
{
	int		i;
	int		size;
	char	**output;
	t_token	*token;

	size = ft_lstsize(lst);
	output = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		token = (t_token *)lst->content;
		output[i] = ft_strdup(token->str);
		lst = lst->next;
		i++;
	}
	output[i] = 0;
	return (output);
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
