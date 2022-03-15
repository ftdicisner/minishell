/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:11:05 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/15 10:57:07 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_var(void *void_var)
{
	t_var *var = (t_var *)void_var;

	printf("# KEY: %s\n# VAL: %s\n\n", var->key, var->value);
}

void debug_env_vars(t_list *head)
{
	printf("######################## ENV VARS: \n");
	ft_lstiter(head, print_var);
}

t_var *path_str_to_var(char *input)
{
	t_var *key_val;
	char **splitted;

	if (input == NULL || input[0] == 0)
		return 0;
	key_val = malloc(sizeof(t_var));
	splitted = ft_split(input, '=');
	key_val->key = splitted[0];
	key_val->value = splitted[1];
	free(splitted);
	return (key_val);
}

t_list *init_env(char **env)
{
	int i;
	t_list *head;
	int n_vars;
	t_var *var;

	n_vars = count_splitted(env);
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