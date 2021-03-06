/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:50:35 by jfrancis          #+#    #+#             */
/*   Updated: 2022/05/31 21:27:59 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the filename passed is valid file.
 * @param node_content t_redir struct, contains the filename and type
 * @return void
 */
static void	t_redir_is_file(void *node_content)
{
	t_redir	*content;

	content = (t_redir *)(node_content);
	if (access(content->file, F_OK) != 0)
	{
		print_error(content->file, NO_SUCH_FILE, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}

static void	init_heredoc(char *tmp_eof)
{
	char	*input;
	int		tmp_in_fd;
	int		tmp_out_fd;

	input = readline("> ");
	tmp_in_fd = open(TMP_FILE, O_TRUNC | O_RDWR | O_CREAT, 0664);
	while (ft_strcmp(input, tmp_eof) != 0)
	{
		if (input)
		{
			write(tmp_in_fd, input, ft_strlen(input));
			write(tmp_in_fd, "\n", 1);
			input = readline("> ");
		}
		else
		{
			printf("here-document warning: wanted `%s'\n", tmp_eof);
			exit(EXIT_SUCCESS);
		}
	}
	free(input);
	close(tmp_in_fd);
	tmp_out_fd = open(TMP_FILE, O_RDONLY);
	dup2(tmp_out_fd, STDIN_FILENO);
}

void	dup_pipes_in(t_shell *shell, t_cmd *cmd, int i)
{
	t_redir	*last;
	int		fd;

	if (cmd->in_r != NULL)
	{
		last = ft_lstlast(cmd->in_r)->content;
		if (last->mode == DOUBLE)
			init_heredoc(last->file);
		else
		{
			ft_lstiter(cmd->in_r, t_redir_is_file);
			fd = ft_open_ronly_file(last);
			dup2(fd, STDIN_FILENO);
		}
		if (i != 0)
			close(shell->pipes[i - 1][1]);
	}
	else if (i != 0)
	{
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
		close(shell->pipes[i - 1][1]);
	}
}
