/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:50:35 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/18 23:26:34 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create the file with the name passed as the function argument
 * node_content->file
 * @param node_content t_redir struct, contains the filename and type
 * @return void
 */
static void	t_redir_is_file(void *node_content)
{
	t_redir *content;

	content = (t_redir *)(node_content);
	if (access(content->file, F_OK) != 0)
		print_error(content->file, NO_SUCH_FILE);
}

/**
 * @brief Iterates through the linked list of t_redir elements
 * and checks if each one exists
 * @param in_r the linked list of t_redir elements
 * @return t_redir* returns the last node of the linked list
 */
static t_redir *check_files(t_list *in_r)
{
	ft_lstiter(in_r, t_redir_is_file);
	return (ft_lstlast(in_r)->content);
}
/**
 * 1 Check if there are redir-in files
 * 2 When reaching a redir of a file that doesn't exist, return error
 * 3 Get the last file of the list.
 * 4 Open the last file to read from it.
 * 5 Redir the STDIN from the filename from step 3
 *
 */
void	dup_pipes_in(t_shell *shell, t_cmd *cmd, int i)
{
	t_redir *last;
	int		fd;

	if (cmd->in_r != NULL)
	{
		last = check_files(cmd->in_r);
		fd = ft_open_file(last);
		dup2(fd, STDIN_FILENO);
	}
	else if (i != 0)
	{
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
		close(shell->pipes[i - 1][1]);
	}
}
