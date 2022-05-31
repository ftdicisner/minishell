/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:15:25 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 18:06:16 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *str)
{
	if (str[0] == '\0')
		return (-1);
	if (str[0] == '<' && str[1] == '<')
		return (IN_DOUBLE_REDIR);
	if (str[0] == '>' && str[1] == '>')
		return (OUT_DOUBLE_REDIR);
	if (str[0] == '<')
		return (IN_SINGLE_REDIR);
	if (str[0] == '>')
		return (OUT_SINGLE_REDIR);
	if (str[0] == '|')
		return (PIPE);
	return (NONE);
}

int	skips_by_type(t_token_type type)
{
	if (type == IN_SINGLE_REDIR || type == OUT_SINGLE_REDIR || type == PIPE)
		return (1);
	if (type == IN_DOUBLE_REDIR || type == OUT_DOUBLE_REDIR)
		return (2);
	return (0);
}

// Find the pointer to the next character in the string
t_token	*get_and_set_subtoken(char *token)
{
	int		i;
	t_token	*subtoken;

	i = 0;
	subtoken = malloc(sizeof(t_token));
	if (token[i] == '\0')
	{
		subtoken->str = ft_strdup("");
		subtoken->type = NONE;
	}
	else
	{
		subtoken->type = get_token_type(token);
		if (skips_by_type(subtoken->type))
			i = i + skips_by_type(subtoken->type);
		else
			while (get_token_type(token + i) == NONE)
				i++;
		subtoken->str = ft_substr(token, 0, i);
	}
	return (subtoken);
}

void	get_subtokens(t_list **tokens, char *token, t_shell *shell)
{
	int		i;
	t_token	*new_token;
	char	*tmp;

	i = 0;
	while (token[i])
	{
		new_token = get_and_set_subtoken(token + i);
		tmp = new_token->str;
		new_token->str = expand_token(tmp, shell->env_vars);
		ft_lstadd_back(tokens, ft_lstnew(new_token));
		i += ft_strlen(tmp);
		free(tmp);
	}
}
