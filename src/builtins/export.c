/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:55:32 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/23 09:00:49 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *find_node_var(t_list *head, char *key)
{
	t_list	*tmp;
	t_var	*var;
	int		key_len;

	tmp = head;
	key_len = ft_strlen(key);
	while (tmp != NULL)
	{
		var = (t_var *)tmp->content;
		if (ft_strlen(var->key) == key_len)
			if (ft_strncmp(var->key, key, key_len) == 0)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_var	*find_var(t_list *head, char *key)
{
	t_list	*new;
	t_var	*var;

	new = find_node_var(head, key);
	if (new != NULL) 
		return (t_var *)(new->content);
	return (NULL);
}

t_list	*export_var(t_list *head, char *key, char *value)
{
	t_list	*new;
	t_var	*var;

	new = find_node_var(head, key);
	if (new != NULL) 
	{
		var = (t_var *)new->content;
		var->value = value;
	}
	else 
	{
		var = malloc(sizeof(t_var));
		var->key = key;
		var->value = value;
		new = ft_lstnew(var);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

// Tests to pass:
// add once: export a=5 
// add multiple: export a=5 b=9 x=10
// add empty: export c=
// add without '=': export x g
// add with multiples '=': export ringo=1=1234=sherlock
// updated var: export a=9 // export a=15 
void	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;
	char	**splitted;

	i = 1;
	while (i < cmd->n_args)
	{
		if (ft_strchr(cmd->args[i], '=') != 0)
		{
			// to-do check if ft_split memory is clear
			splitted = ft_split(cmd->args[i], '=');
			key = ft_strdup(splitted[0]);
			value = ft_strdup(cmd->args[i] + ft_strlen(key) + 1);
			export_var(shell->env_vars, key, value);
			free(splitted);
		}
		i++;
	}
}