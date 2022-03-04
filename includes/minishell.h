/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/02/28 08:49:00 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/libft/src/libft.h"

typedef struct s_cmd {
	char	*name;
	char	**args;
	int		n_args;
	int		is_built;
}				t_cmd;

typedef struct s_shell {
	t_cmd	**cmds;
	int		n_cmds;
	char	*paths;	
}				t_shell;

void	parse_line(char *input, t_shell *shell);


