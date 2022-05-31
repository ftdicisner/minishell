/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:13:49 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 16:57:23 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_mode(t_token_type type, char in_out)
{
	if (in_out == '<' && type == IN_SINGLE_REDIR)
		return (SINGLE);
	if (in_out == '<' && type == IN_DOUBLE_REDIR)
		return (DOUBLE);
	if (in_out == '>' && type == OUT_SINGLE_REDIR)
		return (SINGLE);
	if (in_out == '>' && type == OUT_DOUBLE_REDIR)
		return (DOUBLE);
	return (-1);
}

t_redir	*get_redir(t_list *tokens, char in_out)
{
	t_redir	*redir;
	t_token	*curr_token;
	t_token	*next_token;

	curr_token = (t_token *)tokens->content;
	redir = NULL;
	if (get_redir_mode(curr_token->type, in_out) != -1)
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		redir->mode = get_redir_mode(curr_token->type, in_out);
		if (tokens->next == NULL)
			redir->file = NULL;
		else
		{
			next_token = ((t_token *)tokens->next->content);
			redir->file = ft_strdup(next_token->str);
		}
	}
	return (redir);
}

// Returns a list of t_redir (filenames + mode [single, double])
t_list	*parse_redir(t_list *tokens, char in_out)
{
	t_list	*head;
	t_redir	*new;

	head = NULL;
	while (tokens)
	{
		new = get_redir(tokens, in_out);
		if (new != NULL)
		{
			ft_lstadd_back(&head, ft_lstnew(new));
			tokens = tokens->next;
			if (tokens == NULL)
				break ;
		}
		tokens = tokens->next;
	}
	return (head);
}
