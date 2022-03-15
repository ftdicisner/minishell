/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/11 13:16:17 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libs/libft/src/libft.h"

typedef struct s_cmd {
	char	*name; // cd , echo, ls
	char	**args; // [--help, -lh]
	int		n_args; // 2
	int		is_built; // boolean
}				t_cmd;

typedef struct s_shell {
	t_cmd	**cmds;
	int		n_cmds;
	char	**paths;
}				t_shell;

void	parse_line(char *input, t_shell *shell);
char    **get_path_var(char **envp);

void	builtin_echo(t_cmd *cmd);

#endif