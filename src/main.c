/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:23 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/14 12:08:45 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init(char** env)
{
	t_shell *shell;

	shell = malloc(sizeof(shell));
	shell->paths = get_path_var(env);
	return (shell);
}

int	main(int argc, char **argv, char** env)
{
	char *s;
	t_shell *shell;

	ft_putstr_fd(env[0], 1);
	ft_putchar_fd('\n', 1);

	// REPL -> Read Evaluate Print Loop
	shell = init(env);
	while (s = readline(">>"))
	{
		// printf("%s\n", s);
		add_history(s);
		rl_redisplay();
		parse_line(s, shell);
	}
	return (0);
}