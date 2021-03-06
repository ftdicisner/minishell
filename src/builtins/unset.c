/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:55:29 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 21:33:21 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	free(var->key);
	free(var->value);
	free(var);
}

t_list	*unset_var_aux(t_list *head, t_list *prev, t_list *curr)
{
	t_list	*tmp;

	if (prev == NULL)
	{
		tmp = curr->next;
		ft_lstdelone(curr, del_var);
		return (tmp);
	}
	else
	{
		prev->next = curr->next;
		ft_lstdelone(curr, del_var);
		return (head);
	}
}

t_list	*unset_var(t_list *head, char *key)
{
	t_list	*tmp;
	t_list	*prev;
	t_var	*var;
	size_t	key_len;

	tmp = head;
	prev = NULL;
	key_len = ft_strlen(key);
	while (tmp != NULL)
	{
		var = (t_var *)tmp->content;
		if (ft_strlen(var->key) == key_len)
			if (ft_strncmp(var->key, key, key_len) == 0)
				return (unset_var_aux(head, prev, tmp));
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}

// Tests to pass
// unset one var: unset x
// unset multiple vars: unset x a y z
// unset non-existence var: unset this_var_doesnt_exist
int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int		i;

	i = 1;
	while (i < cmd->n_args)
	{
		shell->env_vars = unset_var(shell->env_vars, cmd->args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
