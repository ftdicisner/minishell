/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:55:49 by dicisner          #+#    #+#             */
/*   Updated: 2022/06/01 19:20:38 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

t_token	*new_token(char *str, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = type;
	token->str = str;
	return (token);
}

// Return a string token by checking if there is a variable
// that needs to be evaluated
void	*get_set_token(t_list **tokens, char *start, char *end, t_shell *shell)
{
	t_token	*token;
	char	*tmp;

	if (*start == '\'')
	{
		token = new_token(ft_substr(start, 1, end - start - 2), SINGLE_QUOTES);
		ft_lstadd_back(tokens, ft_lstnew(token));
	}
	else if (*start == '"')
	{
		tmp = ft_substr(start + 1, 0, end - start - 2);
		token = new_token(expand_token(tmp, shell->env_vars), DOUBLE_QUOTES);
		ft_lstadd_back(tokens, ft_lstnew(token));
		free(tmp);
	}
	else
	{
		tmp = ft_substr(start, 0, end - start);
		get_subtokens(tokens, tmp, shell);
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
			return (lst);
		get_set_token(&lst, start, end, shell);
	}
	return (lst);
}
