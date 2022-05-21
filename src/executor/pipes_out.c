/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:59:22 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/19 20:32:33 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create the file with the name passed as the function argument
 * node_content->file
 * @param node_content t_redir struct, contains the filename and type
 * @return void
 */
void	t_redir_cb(void *node_content)
{
	t_redir *content;
	int		fd;

	content = (t_redir *)(node_content);
	fd = open(content->file, O_CREAT, 0664);
	close(fd);
}

/**
 * @brief Iterates through the linked list of t_redir elements
 * and create a file for each of those nodes
 * @param out_r the linked list of t_redir elements
 * @return t_redir* return the last node of the linked list
 */
t_redir	*create_files(t_list *out_r)
{
	ft_lstiter(out_r, t_redir_cb);
	return (ft_lstlast(out_r)->content);
}

/**
 * 1 Check if there are redir-out files
 * 2 Create all files in the redir-out list
 * 3 Get the last file of the list, filename and type
 * 4 Open the file to write (Append or normal depending on the mode)
 * 5 Redir the STDOUT to the filename from the step 3
 *
 */
void	dup_pipes_out(t_shell *shell, t_cmd *cmd, int i)
{
	t_redir *last;
	int		fd;

	if (cmd->out_r != NULL)
	{
		last = create_files(cmd->out_r);
		fd = ft_open_wronly_file(last);
		dup2(fd, STDOUT_FILENO);
	}
	else if (shell->n_cmds != 1 && i != shell->n_cmds - 1)
	{
		dup2(shell->pipes[i][1], STDOUT_FILENO);
		close(shell->pipes[i][0]);
	}
}