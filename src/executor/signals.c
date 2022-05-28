/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:41:46 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/27 20:49:53 by dicisner         ###   ########.fr       */
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

void	handle_sig_ignore(int sig)
{
	if (sig == SIGINT)
		g_cmd_status = 130;
}

void	handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_cmd_status = 130;
		exit(130);
	}
}

void	config_signal(t_sigaction *action, void (*handler)(int), int signum)
{
	action->sa_handler = handler;
	action->sa_flags = SA_RESTART;
	sigemptyset(&action->sa_mask);
	sigaction(signum, action, NULL);
}
