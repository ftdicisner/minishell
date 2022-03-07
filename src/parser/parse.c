/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:16:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/07 09:28:59 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
 * What to do here?
 * Receive a line of text
 * that might contain commands, arguments
 * pipes
 * We need to split them by spaces, pipes
 * identify which part is the command and which
 * are the arguments
*/

/**
 * How to store them?
 * char ***
 * char ** ["cd"] ["asdf"] [0]
 * char ** ["echo"] ["asdf"] ["saf"] [0]
 * char ** 0
*/

int	count_splitted(char **s_arr)
{
	int n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

// ['cd diego paco', 'echo diego']
void	split_cmd_args(char **s_by_pipes, t_shell *shell)
{
	t_cmd	**cmds;
	t_cmd	*cmd;
	char	**splitted_args;
	int		n_commands;
	int		n_args;
	int		j;
	int		i;

	n_commands = count_splitted(s_by_pipes);
	cmds = malloc(sizeof(t_cmd *) * (n_commands));
	i = 0;
	while (i < n_commands)
	{
		cmd = malloc(sizeof(t_cmd));
		// ['cd', 'diego', 'paco']
		splitted_args = ft_split(s_by_pipes[i], ' ');
		j = 0;
		if (splitted_args != 0)
		{
			n_args = count_splitted(splitted_args) - 1;
			cmd->name = splitted_args[0];
			cmd->args = malloc(sizeof(char *) * n_args);
			while (j < n_args) 
			{
				cmd->args[j] = splitted_args[j + 1];
				j++;
			}
			cmd->n_args = n_args;
		}
		cmds[i] = cmd;
		i++;
	}
	shell->n_cmds = n_commands;
	shell->cmds = cmds;
}

void	debug_print_parsed_info(t_shell *shell)
{
	int i = 0;

	while (i < shell->n_cmds)
	{

		printf("CMD %d: %s ARGS: [", i, shell->cmds[i]->name);
		int j = 0;
		while (j < shell->cmds[i]->n_args)
		{
			printf("%s",shell->cmds[i]->args[j]);
			if (j != shell->cmds[i]->n_args - 1) {
				printf(",");
			}
			j++;
		}
		printf("]\n");
		i++;
	}
}

void	parse_line(char *input, t_shell *shell)
{
	char 	**splitted_by_pipe;

	splitted_by_pipe = ft_split(input, '|');
	split_cmd_args(splitted_by_pipe, shell);
	debug_print_parsed_info(shell);
}