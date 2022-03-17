/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:08:41 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/16 10:36:30 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_splitted(char **s_arr)
{
	int n;

	n = 0;
	while (s_arr[n] != 0)
	{
		n++;
	}
	return (n);
}

int    ft_strcmp(char *s1, char *s2)
{
    int s1_len;
    int s2_len;

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);

    if (s1_len != s2_len)
        return (1);
    else
        return(ft_strncmp(s1, s2, s1_len));
}