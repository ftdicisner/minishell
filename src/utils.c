/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:08:41 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/21 09:43:50 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_splitted(char **s_arr)
{
	int	n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (1);
	else
		return (ft_strncmp(s1, s2, s1_len));
}

char	**lststr_to_arr(t_list *lst)
{
	int		i;
	int		size;
	char	**output;

	size = ft_lstsize(lst);
	output = malloc((sizeof(char *) * size) + 1);
	i = 0;
	while (i < size)
	{
		output[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	output[i] = 0;
	return (output);
}