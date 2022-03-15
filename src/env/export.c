/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:55:32 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/15 11:00:25 by dicisner         ###   ########.fr       */
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
	{
		return (t_var *)(new->content);
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