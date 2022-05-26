/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:11:05 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/25 18:28:04 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var *path_str_to_var(char *input)
{
	t_var	*key_val;
	char	**splitted;

	if (input == NULL || input[0] == 0)
		return (NULL);
	key_val = malloc(sizeof(t_var));
	splitted = ft_split(input, '=');
	key_val->key = ft_strdup(splitted[0]);
	key_val->value = ft_strdup(input + ft_strlen(splitted[0]) + 1);
	free_array(splitted);
	return (key_val);
}

t_list *init_env(char **env)
{
	int i;
	t_list *head;
	int n_vars;
	t_var *var;

	n_vars = count_splitted_2d(env);
	if (n_vars > 0)
	{
		var = path_str_to_var(env[0]);
		head = ft_lstnew(var);
		i = 1;
		while (env[i] != NULL)
		{
			var = path_str_to_var(env[i]);
			ft_lstadd_back(&head, ft_lstnew(var));
			i++;
		}
	}
	return (head);
}

char	**lst_env_to_strs(t_list *env)
{
	int		size;
	int		i;
	char	**output;
	char	*prefix;
	char	*tmp;

	size = ft_lstsize(env);
	output = ft_calloc(size + 1, sizeof(char*));
	i = 0;
	while (i < size)
	{
		prefix = ft_strjoin(((t_var *)env->content)->key, "=");
		tmp = ft_strjoin(prefix, ((t_var *)env->content)->value);
		free(prefix);
		output[i] = tmp;
		env = env->next;
		i++;	
	}
	return (output);
}