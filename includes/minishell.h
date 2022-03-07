/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/07 09:58:58 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


