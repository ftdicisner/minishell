/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:27 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/24 22:16:02 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	keyPressed(int count, int key)
// {
// 	(void)count;

// 	rl_replace_line("hello", 0);
// 	return (0);
// }

// int	keyPressed2(int count, int key)
// {
// 	(void)count;
	
// 	printf("Key pressed: %d\n", key);
// 	// rl_on_new_line();
// 	// rl_replace_line("hello", 0);
// 	rl_redisplay();
// 	return (0);
// }

// int	tests_readline()
// {
// 	char *s;

// 	rl_bind_key(27, keyPressed);
// 	rl_bind_key(92, keyPressed2);
// 	while (s = readline(">>"))
// 	{
// 		printf("%s\n", s);
// 		add_history(s);
// 		rl_redisplay();
// 	}
// 	return (0);
// }