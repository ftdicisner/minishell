/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:16:34 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/30 20:42:49 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Move array of arguments to a t_list and them
// generate the t_cmd information
void	lst_to_cmd(char **args, t_cmd *cmd)
{
	t_list	*lst;
	int		size;

	lst = parse_cmd(args);
	size = ft_lstsize(lst);
	if (size > 0)
	{
		cmd->name = ft_strdup(lst->content);
		cmd->n_args = size;
		cmd->args = lststr_to_arr(lst);
	}
	else
	{
		cmd->name = 0;
		cmd->n_args = 0;
		cmd->args = 0;
	}
	ft_lstclear(&lst, free);
}

t_cmd	*create_cmd(char **cmd_str)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd_str != 0)
	{
		lst_to_cmd(cmd_str, cmd);
		cmd->in_r = parse_redir(cmd_str, '<');
		cmd->out_r = parse_redir(cmd_str, '>');
	}
	return (cmd);
}

// Receives ['cd diego paco', 'echo diego'] and sets the cmds
// in the form cmd struct
void	split_cmd_args(char ***s_by_pipes, t_shell *shell)
{
	t_cmd	**cmds;
	int		n_commands;
	int		i;

	n_commands = count_splitted_3d(s_by_pipes);
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
	t_list	*tokens;
	char	***tokens_by_pipes;

	tokens = input_to_tokens_lst(input, shell);
	tokens_by_pipes = split_tokens_by_pipes(tokens);
	split_cmd_args(tokens_by_pipes, shell);
	free_tokens(tokens_by_pipes, tokens);
}
