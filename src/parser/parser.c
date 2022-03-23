/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:16:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/23 11:01:37 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_to_cmd(char **args, t_cmd *cmd)
{
	t_list *lst;
	int		size;
	int		i;

	lst = parse_cmd(args);
	size = ft_lstsize(lst);
	if (size > 0)
	{
		cmd->name = ft_strdup(lst->content);
		cmd->n_args = size;
		cmd->args = lststr_to_arr(lst);
	}
	else {
		cmd->name = 0;
		cmd->n_args = 0;
		cmd->args = 0;
	}
}

t_cmd	*create_cmd(char *cmd_str)
{
	t_cmd	*cmd;
	int		i;
	char	**splitted_args;
	int		n_args;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	splitted_args = ft_split(cmd_str, ' ');
	if (splitted_args != 0)
	{
		// to-do free the list used here
		lst_to_cmd(splitted_args, cmd);
		cmd->in_r = parse_redir(splitted_args, '<');
		cmd->out_r = parse_redir(splitted_args, '>');
	}
	return (cmd);
}

// ['cd diego paco', 'echo diego']
void	split_cmd_args(char **s_by_pipes, t_shell *shell)
{
	t_cmd	**cmds;
	int		n_commands;
	int		i;

	n_commands = count_splitted(s_by_pipes);
	cmds = malloc(sizeof(t_cmd *) * (n_commands));
	i = 0;
	while (i < n_commands)
	{
		cmds[i] = create_cmd(s_by_pipes[i]);
		i++;
	}
	shell->n_cmds = n_commands;
	shell->cmds = cmds;
}

// Tests to pass:
// commands w arguments: echo xyz abc
// commands wo arguments: cd
// commands w pipes: echo abc def | grep de
// commands w redirect: echo test > foo
// commands w many redirect: echo test > foo < bar << gold
// commands w many redirect in different positions: < tes < foo echo homer >> go
void	parse_line(char *input, t_shell *shell)
{
	char 	**splitted_by_pipe;

	splitted_by_pipe = ft_split(input, '|');
	split_cmd_args(splitted_by_pipe, shell);
	// debug_print_parsed_info(shell);
}

//  DEBUG STUFF

void	print_r_dir(void *r_dir)
{
	t_redir *new;

	new = (t_redir *)r_dir;
	printf("[file: %s type: %d],", new->file, new->mode);
}

void	debug_print_parsed_info(t_shell *shell)
{
	int i = 0;

	while (i < shell->n_cmds)
	{
		t_cmd *cmd = shell->cmds[i];
		printf("CMD %d: %s ARGS: [", i, cmd->name);
		int j = 0;
		while (j < cmd->n_args)
		{
			printf("%s",cmd->args[j]);
			if (j != cmd->n_args - 1) {
				printf(",");
			}
			j++;
		}
		printf("]\n");
		j = 0;
		printf("IN-FILES: [");
		ft_lstiter(cmd->in_r, print_r_dir);
		printf("]\n");
		printf("OUT-FILES: [");
		ft_lstiter(cmd->out_r, print_r_dir);
		printf("]\n\n");
		i++;
	}
}