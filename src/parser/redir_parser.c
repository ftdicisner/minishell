/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:13:49 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 13:34:31 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*find_redir(char **args, char in_out, int *i)
{
	t_redir	*redir;
	int		j;

	redir = malloc(sizeof(t_redir));
	j = 0;
	while (args[*i][j] == in_out)
		j++;
	if (j < 3)
	{
		if (j == 2)
			redir->mode = DOUBLE;
		else
			redir->mode = SINGLE;
		if (args[*i][j] == 0 && *i + 1 < count_splitted_2d(args))
		{
			redir->file = ft_strdup(args[*i + 1]);
			*i = *i + 1;
		}
		else
			redir->file = ft_strdup(args[*i] + j);
		return (redir);
	}
	return (NULL);
}

// Returns a list of t_redir (filenames + mode [single, double])
t_list	*parse_redir(char **args, char in_out)
{
	int		i;
	int		n_args;
	t_list	*head;
	t_redir	*new;

	n_args = count_splitted_2d(args);
	head = NULL;
	i = 0;
	while (i < n_args)
	{
		if (args[i][0] == in_out)
		{
			new = find_redir(args, in_out, &i);
			if (new != NULL)
				ft_lstadd_back(&head, ft_lstnew(new));
		}
		i++;
	}
	return (head);
}
