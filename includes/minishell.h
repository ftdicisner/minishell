/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/15 11:00:45 by dicisner         ###   ########.fr       */
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
	t_list	*env_vars;
}				t_shell;

typedef struct	s_var
{
	char *key;
	char *value;
}				t_var;

void	parse_line(char *input, t_shell *shell);
char    **get_path_var(char **envp);
int		count_splitted(char **s_arr);
t_list	*init_env(char **env);
t_list	*export_var(t_list *head, char *key, char *value);
t_list	*unset_var(t_list *head, char *key);
t_var	*find_var(t_list *head, char *key);

// Debug
void	debug_env_vars(t_list *head);
void	debug_print_parsed_info(t_shell *shell);