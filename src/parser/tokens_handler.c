/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:35:18 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 12:12:55 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*end_position_env(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\'')
			i++;
	else
		while (str[i] != '\0' && str[i] != '$')
			i++;
	return (str + i);
}

char	*get_substr_env(char *str, t_list *env_vars)
{
	char	*token;
	char	*end;
	t_var	*var;

	end = end_position_env(str);
	if (*str == '$')
	{
		token = ft_substr(str, 1, end - str - 1);
		var = find_var(env_vars, token);
		free(token);
		if (var)
			return (ft_strdup(var->value));
		else
			return (ft_strdup(""));
	}
	token = ft_substr(str, 0, end - str);
	return (token);
}

// Receives an string and separates it into
// string by spaces and $
t_list	*split_by_env(char *str, t_list *env_vars)
{
	t_list	*list;
	int		i;
	char	*token;

	list = NULL;
	i = 0;
	while (str[i] != 0)
	{
		token = get_substr_env(str + i, env_vars);
		i = end_position_env(str + i) - str;
		ft_lstadd_back(&list, ft_lstnew(token));
	}
	return (list);
}

// Check if there are env vars in the token
// and return a new string with the env vars
// values replaced
char	*expand_token(char *token, t_list *env_vars)
{
	char	*str;
	char	*tmp;
	t_list	*tmp_list;
	t_list	*list;

	list = split_by_env(token, env_vars);
	tmp_list = list;
	if (ft_lstsize(tmp_list) == 1)
	{
		tmp = ft_strdup((char *)tmp_list->content);
		ft_lstclear(&list, free);
		return (tmp);
	}
	str = ft_strdup((char *)tmp_list->content);
	while (tmp_list->next)
	{
		tmp = str;
		str = ft_strjoin(str, (char *)tmp_list->next->content);
		free(tmp);
		tmp_list = tmp_list->next;
	}
	ft_lstclear(&list, free);
	return (str);
}
