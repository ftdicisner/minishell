/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:33:10 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/20 20:32:41 by dicisner         ###   ########.fr       */
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

int		builtin_env(t_cmd *cmd, t_shell *shell)
{
	if (cmd->n_args > 1)
	{
		printf(TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	else 
	{
		ft_lstiter(shell->env_vars, print_var);
		return (EXIT_SUCCESS);
	}
}