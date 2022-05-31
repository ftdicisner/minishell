/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:55:49 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/30 17:59:18 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_pointer_no_blank(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

// Return a pointer to the end of the string token
char	*token_end_pos(char *str, int start_pos)
{
	int		i;
	char	start_char;

	start_char = str[start_pos];
	i = start_pos + 1;
	if (start_char == '\'' || start_char == '"')
	{
		while (str[i] != '\0' && str[i] != start_char)
			i++;
		if (str[i] != '\0')
			return (str + i + 1);
		else
			return (NULL);
	}
	if (start_char == '|')
		return (str + start_pos + 1);
	else
	{
		while (str[i] != '\0' && str[i] != ' ')
			i++;
		return (str + i);
	}
}

// Return a pointer to the start of a string token
char	*token_start_pos(char *str)
{
	char	*next;

	next = next_pointer_no_blank(str);
	return (next);
}

// Return a string token by checking if there is a variable
// that needs to be evaluated
t_token	*get_token(char *start, char *end, t_shell *shell)
{
	t_token	*token;
	char	*tmp;

	token = malloc(sizeof(t_token));
	if (*start == '\'')
	{
		token->str = ft_substr(start + 1, 0, end - start - 2);
		token->type = SINGLE_QUOTES;
	}
	else if (*start == '"')
	{
		tmp = ft_substr(start + 1, 0, end - start - 2);
		token->str = expand_token(tmp, shell->env_vars);
		token->type = DOUBLE_QUOTES;
		free(tmp);
	}
	else
	{
		tmp = ft_substr(start, 0, end - start);
		token->str = expand_token(tmp, shell->env_vars);
		token->type = SPACES;
		free(tmp);
	}
	return (token);
}

// Return a list of tokens from a input string
// A token can be a string surronded by blank spaces, a pipe, 
// a string surrounded by quotes, expand env variables if needed
t_list	*input_to_tokens_lst(char *input, t_shell *shell)
{
	t_list	*lst;
	t_token	*token;
	char	*start;
	char	*end;

	lst = NULL;
	start = input;
	end = input;
	while (*end != '\0')
	{
		start = token_start_pos(end);
		if (*start == '\0')
			return (lst);
		end = token_end_pos(start, 0);
		if (end == NULL)
			return (NULL);
		token = get_token(start, end, shell);
		if (token == NULL)
			return (NULL);
		ft_lstadd_back(&lst, ft_lstnew(token));
	}
	return (lst);
}
