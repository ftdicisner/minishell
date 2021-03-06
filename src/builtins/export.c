/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:55:32 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 20:57:25 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the node with the given key
t_list	*find_node_var(t_list *head, char *key)
{
	t_list	*tmp;
	t_var	*var;
	size_t	key_len;

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

t_list	*export_var(t_list *head, char *key, char *value)
{
	t_list	*new;
	t_var	*var;

	new = find_node_var(head, key);
	if (new != NULL)
	{
		var = (t_var *)new->content;
		free(key);
		free(var->value);
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

// Returns the node content (t_var) with the given key
t_var	*find_var(t_list *head, char *key)
{
	t_list	*new;

	if (ft_strlen(key) == 1 && key[0] == '?')
		export_var(head, ft_strdup("?"), ft_itoa(g_cmd_status));
	new = find_node_var(head, key);
	if (new != NULL)
		return ((t_var *)(new->content));
	return (NULL);
}

char	*find_first_no_blank(char *input)
{
	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

// Tests to pass:
// add once: export a=5
// add multiple: export a=5 b=9 x=10
// add empty: export c=
// add without '=': export x g
// add with multiples '=': export ringo=1=1234=sherlock
// updated var: export a=9 // export a=15
// export 'blue =azul' should be error (done)
// export 'blue= azul' should export 'azul'
// export blue =azul should be error (done)
int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;
	char	**splitted;

	i = 1;
	if (cmd->n_args == 1)
		return (print_error("export", "no variable defined", EXIT_SUCCESS));
	while (i < cmd->n_args)
	{
		if (ft_strchr(cmd->args[i], '=') != 0)
		{
			if (find_first_no_blank(cmd->args[i])[0] == '=')
				return (print_error_export(cmd->args[i], EXIT_FAILURE));
			splitted = ft_split(cmd->args[i], '=');
			key = ft_strdup(splitted[0]);
			if (ft_strchr(key, ' ') != 0)
				return (print_error_export(cmd->args[i], EXIT_FAILURE));
			value = ft_strdup(cmd->args[i] + ft_strlen(key) + 1);
			export_var(shell->env_vars, key, value);
			free_array(splitted);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
