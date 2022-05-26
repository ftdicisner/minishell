/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:29:18 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 13:33:38 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, "|") == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_tokens_b4_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, "|") != 0)
			count++;
		else
			return (count);
		tmp = tmp->next;
	}
	return (count);
}

void	split_tokens_aux(char ***by_pipes, int i, t_list **lst)
{
	int	j;
	int	n_tokens;

	n_tokens = count_tokens_b4_pipes(*lst);
	by_pipes[i] = malloc(sizeof(char *) * (n_tokens + 1));
	j = 0;
	while (j < n_tokens)
	{
		by_pipes[i][j] = ft_strdup((*lst)->content);
		*lst = (*lst)->next;
		j++;
	}
	by_pipes[i][j] = NULL;
}

char	***split_tokens_by_pipes(t_list *tokens)
{
	char	***tokens_by_pipes;
	t_list	*lst;
	int		i;
	int		n_cmds;

	i = 0;
	n_cmds = count_pipes(tokens) + 1;
	tokens_by_pipes = malloc(sizeof(char **) * (n_cmds + 1));
	lst = tokens;
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, "|") != 0)
		{
			split_tokens_aux(tokens_by_pipes, i, &lst);
			i++;
		}
		else
			lst = lst->next;
	}
	tokens_by_pipes[i] = NULL;
	return (tokens_by_pipes);
}

char	***generate_tokens(char *input, t_shell *shell)
{
	t_list	*tokens;
	char	***tokens_by_pipes;

	tokens = input_to_tokens_lst(input, shell);
	tokens_by_pipes = split_tokens_by_pipes(tokens);
	ft_lstclear(&tokens, free);
	return (tokens_by_pipes);
}
