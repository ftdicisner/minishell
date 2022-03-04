/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/03 11:07:36 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init()
{
	t_shell *shell;

	shell = malloc(sizeof(shell));
	return (shell);
}

int	main(int argc, char **argv, char** env)
{
	char *s;
	t_shell *shell;

	ft_putstr_fd(env[0], 1);
	ft_putchar_fd('\n', 1);

	// REPL -> Read Evaluate Print Loop asdfaa
	shell = init();
	while (s = readline(">>"))
	{
		printf("%s\n", s);
		add_history(s);
		rl_redisplay();
		parse_line(s, shell);
	}
	return (0);
}