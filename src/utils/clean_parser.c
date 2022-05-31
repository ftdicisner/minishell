/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:25:39 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/30 20:42:20 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	free(t->str);
	free(t);
}

// free each string and each array
// of an array of an array of strings
int	free_tokens(char ***tokens, t_list *tokens_lst)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			free(tokens[i][j]);
			j++;
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
	ft_lstclear(&tokens_lst, free_token);
	return (EXIT_SUCCESS);
}

//Close opened file descriptor
void	close_all_fds(void)
{
	int	fd;

	fd = open(TMP_FILE, O_RDONLY | O_CREAT);
	close(fd + 1);
	while (fd > 2)
		close(fd--);
	unlink(TMP_FILE);
}
