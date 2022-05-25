/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:50:17 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/24 22:17:34 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	omit_redir(char **args, char in_out, int i)
{
	int		j;

	j = 0;
	while (args[i][j] == in_out) 
		j++;
	if (j < 3)
	{
		if (args[i][j] == 0 && i + 1 < count_splitted_2d(args))
			return (2);
		else
			return (1);
	}
	return (0);
}

t_list	*parse_cmd(char **args)
{
	int		i;
	int		n_args;
	t_list	*head;
	char	first;
	int		skips;

	n_args = count_splitted_2d(args);
	head = NULL;
	i = 0;
	while (i < n_args)
	{
		first = args[i][0];
		skips = 0;
		if (first == '<' || first == '>')
			skips = omit_redir(args, first, i);
		if (skips == 0)
		{
			ft_lstadd_back(&head, ft_lstnew(ft_strdup(args[i])));
			skips = 1;
		}
		i = i + skips;
	}
	return (head);
}