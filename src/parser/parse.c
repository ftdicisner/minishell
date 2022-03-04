/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:16:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/02/28 08:51:05 by dicisner         ###   ########.fr       */
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

void	split_cmd_args(char **s_by_pipes, t_shell *shell)
{
	t_cmd	**cmds;
	t_cmd	*cmd;
	int		n_commands;
	int		i;

	cmds = malloc(sizeof(t_cmd *) * (n_commands));
	i = 0;
	while (i < n_commands)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->args = ft_split(s_by_pipes[i], ' ');
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
		printf("ARG %d: %s", i, shell->cmds[i]->args[0]);
	}
}

void	parse_line(char *input, t_shell *shell)
{
	char 	**splitted_by_pipe;
	int		n_commands;	

	splitted_by_pipe = ft_split(input, '|');
	split_cmd_args(splitted_by_pipe, shell);
	debug_print_parsed_info(shell);
}