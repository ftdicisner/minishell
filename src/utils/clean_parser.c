/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:25:39 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/24 20:27:54 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free each string and each array
// of an array of an array of strings
int		free_tokens_arr(char ***tokens)
{
	int i;
	int j;

	i = 0;
	while(tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			free(tokens[i][j]);
			j++;
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (EXIT_SUCCESS);
}