/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:29:18 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/22 23:04:47 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp((char*)tmp->content, "|") == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int		count_tokens_b4_pipes(t_list *tokens)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp((char*)tmp->content, "|") != 0)
			count++;
		else
			return (count);
		tmp = tmp->next;
	}
	return (count);
}

char	**split_tokens_aux(char ***by_pipes, int i, t_list **lst)
{
	int j;
	int n_tokens;

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

	i = 0;
	tokens_by_pipes = malloc(sizeof(char **) * (count_pipes(tokens) + 1));
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
	// TODO Free the list of tokens lst
	tokens_by_pipes = split_tokens_by_pipes(tokens);
	return (tokens_by_pipes);
}

// Region debug


// print the strings content of each t_list
void	print_list(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
}

void	debug_quotes(char *input, t_shell *shell)
{
	t_list *tokens = input_to_tokens_lst(input, shell);

	// print_list(tokens);

	char	***tokens_by_pipes = split_tokens_by_pipes(tokens);
	char	*token;

	int i = 0;
	while (tokens_by_pipes[i] != 0)
	{
		int j = 0;
		while (tokens_by_pipes[i][j] != 0)
		{
			token = tokens_by_pipes[i][j];
			token = expand_token(token, shell->env_vars);
			printf("%s-", token);
			j++;
		}
		i++;
		printf("\n");
	}

	printf("\n");
}