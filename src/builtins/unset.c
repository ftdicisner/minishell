/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:55:29 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/15 10:56:47 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	free(content);
}

t_list	*unset_var_aux(t_list *head, t_list *prev, t_list *curr)
{
	if (prev == NULL)
	{
		ft_lstdelone(curr, del_var);
		return (curr);
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
	int		key_len;

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