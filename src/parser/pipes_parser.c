/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:29:18 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 21:31:26 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_token(t_token *token)
{
	if (token->type == PIPE)
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

void	split_tokens_aux(t_list **by_pipes, int i, t_list **lst)
{
	int		j;
	int		n_tokens;
	t_token	*token;
	t_token	*new_token;

	n_tokens = count_tokens_b4_pipes(*lst);
	by_pipes[i] = NULL;
	j = 0;
	while (j < n_tokens)
	{
		token = (t_token *)(*lst)->content;
		new_token = malloc(sizeof(t_token));
		new_token->str = ft_strdup(token->str);
		new_token->type = token->type;
		ft_lstadd_back(by_pipes + i, ft_lstnew(new_token));
		*lst = (*lst)->next;
		j++;
	}
}

t_list	**split_tokens_by_pipes(t_list *tokens)
{
	t_list	**tokens_by_pipes;
	int		i;

	i = 0;
	if (!tokens)
		return (NULL);
	tokens_by_pipes = malloc(sizeof(t_list *) * (count_pipes(tokens) + 2));
	if (is_pipe_token((t_token *)tokens->content))
	{
		split_tokens_aux(tokens_by_pipes, i, &tokens);
		i++;
	}
	while (tokens)
	{
		if (!is_pipe_token((t_token *)tokens->content))
		{
			split_tokens_aux(tokens_by_pipes, i, &tokens);
			i++;
		}
		else
			tokens = tokens->next;
	}
	tokens_by_pipes[i] = NULL;
	return (tokens_by_pipes);
}
