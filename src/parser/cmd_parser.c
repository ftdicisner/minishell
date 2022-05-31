/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:50:17 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 18:06:40 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token_type type)
{
	if (type == IN_SINGLE_REDIR || type == OUT_DOUBLE_REDIR
		|| type == OUT_SINGLE_REDIR || type == IN_DOUBLE_REDIR)
		return (1);
	return (0);
}

int	is_common_arg(t_token_type type)
{
	if (type == NONE || type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
		return (1);
	return (0);
}

t_list	*parse_cmd(t_list *tokens)
{
	int		redir_flag;
	t_list	*head;
	t_token	*token;

	head = NULL;
	redir_flag = 0;
	while (tokens)
	{
		token = tokens->content;
		if (is_common_arg(token->type) && redir_flag == 0)
			ft_lstadd_back(&head, ft_lstnew(ft_strdup(token->str)));
		redir_flag = 0;
		if (is_redir(token->type))
			redir_flag = 1;
		tokens = tokens->next;
	}
	return (head);
}
