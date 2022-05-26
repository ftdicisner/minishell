/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:41:46 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/26 12:52:06 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_cmd_status = 130;
	}
}

void	config_signal(t_sigaction *action, void (*handler)(int), int signum)
{
	action->sa_handler = handler;
	action->sa_flags = 0;
	sigemptyset(&action->sa_mask);
	sigaction(signum, action, NULL);
}
