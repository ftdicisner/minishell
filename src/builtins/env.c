/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:33:10 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/16 09:41:46 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_var(void *void_var)
{
	t_var *var;
	
	var = (t_var *)void_var;
	printf("%s=%s\n", var->key, var->value);
}

void debug_env_vars(t_list *head)
{
	printf("######################## ENV VARS: \n");
	ft_lstiter(head, print_var);
}

void	builtin_env(t_cmd *cmd, t_shell *shell)
{
	if (cmd->n_args > 1)
	{
		printf("Error\n");
	}
	else 
	{
		ft_lstiter(shell->env_vars, print_var);
	}
}