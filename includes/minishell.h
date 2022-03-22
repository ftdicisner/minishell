/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/03/21 13:23:33 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libs/libft/src/libft.h"

# define TOO_MANY_ARGS "Too many arguments."
# define NO_SUCH_FILE "No such file or directory."
# define INVALID_INPUT "Invalid input."

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

// parser
void	parse_line(char *input, t_shell *shell);
char    **get_path_var(char **envp);
t_list	*init_env(char **env);
t_list	*export_var(t_list *head, char *key, char *value);
t_list	*unset_var(t_list *head, char *key);
t_var	*find_var(t_list *head, char *key);
int		ft_strcmp(char *s1, char *s2);
char	*concat_strs(char **input);

// builtins
void	builtin_echo(t_cmd *cmd, t_shell *shell);
void	builtin_env(t_cmd *cmd, t_shell *shell);
int		builtin_cd(t_cmd *cmd, t_shell *shell);
void	builtin_pwd(t_cmd *cmd, t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);


// executor
void	executor(t_shell *shell);

// utils
int		count_splitted(char **s_arr);
int		ft_strcmp(char *s1, char *s2);
void	print_error(char *cmd, char *error_msg);
void	parse_env_var(int i, t_cmd *cmd, t_shell *shell);
void	print_env_var_val(int i, t_cmd *cmd, t_shell *shell);

// Debug
void	debug_env_vars(t_list *head);
void	debug_print_parsed_info(t_shell *shell);

#endif
