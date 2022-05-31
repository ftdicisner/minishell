/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:25:39 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 12:07:16 by dicisner         ###   ########.fr       */
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

// free each token in the list of list of tokens
// aka 2d list
int	free_tokens(t_list **tokens, t_list *tokens_lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (tokens[i])
	{
		tmp = tokens[i];
		ft_lstclear(&tmp, free_token);
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
