/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:32:45 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/31 21:32:00 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_splitted_2d(char **s_arr)
{
	int	n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

int	count_splitted_3d(char ***s_arr)
{
	int	n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

int	count_lst_lst(t_list **lst)
{
	int	n;

	n = 0;
	if (!lst)
		return (n);
	while (lst[n] != 0)
	{
		n++;
	}
	return (n);
}
