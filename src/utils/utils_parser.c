/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:32:45 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 16:56:18 by jfrancis         ###   ########.fr       */
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
