/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:29:18 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/30 18:25:17 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_token(t_token * token)
{
	if (ft_strcmp(token->str, "|") == 0 && token->type == SPACES)
		return (1);
	else
		return (0);
}

int	count_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;
	t_token	*token;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (is_pipe_token(token))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_tokens_b4_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;
	t_token	*token;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (is_pipe_token(token))
			return (count);
		else
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	split_tokens_aux(char ***by_pipes, int i, t_list **lst)
{
	int		j;
	int		n_tokens;
	t_token	*token;

	n_tokens = count_tokens_b4_pipes(*lst);
	by_pipes[i] = malloc(sizeof(char *) * (n_tokens + 1));
	j = 0;
	while (j < n_tokens)
	{
		token = (t_token *)(*lst)->content;
		by_pipes[i][j] = ft_strdup(token->str);
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
	if (is_pipe_token((t_token *)lst->content))
	{
		split_tokens_aux(tokens_by_pipes, i, &lst);
		i++;
	}
	while (lst)
	{
		if (!is_pipe_token((t_token *)lst->content))
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
