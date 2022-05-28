/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:43:50 by dicisner          #+#    #+#             */
/*   Updated: 2022/05/27 21:01:10 by dicisner         ###   ########.fr       */
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
# include <fcntl.h>

# include "../libs/libft/src/libft.h"

# define TOO_MANY_ARGS "Too many arguments."
# define NO_SUCH_FILE "No such file or directory."
# define INVALID_INPUT "Invalid input."
# define COMMAND_NOT_FOUND "Command not found."
# define TMP_FILE "/tmp/heredoc_tmp"

extern int					g_cmd_status;

typedef struct sigaction	t_sigaction;

/* < or << */
typedef enum e_redir_mode {
	SINGLE,
	DOUBLE
}		t_redir_mode;

typedef struct s_redir {
	char			*file;
	t_redir_mode	mode;
}				t_redir;

typedef struct s_cmd {
	char	*name;
	char	**args;
	int		n_args;
	int		is_built;
	t_list	*in_r;
	t_list	*out_r;
}				t_cmd;

typedef struct s_shell {
	t_cmd		**cmds;
	int			n_cmds;
	t_list		*env_vars;
	int			**pipes;
	t_sigaction	*action;
}				t_shell;

typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

// parser
void	parse_line(char *input, t_shell *shell);
char	**get_path_var(t_shell *shell);
t_list	*init_env(char **env);
t_list	*export_var(t_list *head, char *key, char *value);
t_list	*unset_var(t_list *head, char *key);
t_var	*find_var(t_list *head, char *key);
int		ft_strcmp(char *s1, char *s2);
char	*concat_strs(char **input);
char	**lst_env_to_strs(t_list *env);
t_list	*parse_redir(char **args, char in_out);
t_list	*parse_cmd(char **args);
char	***generate_tokens(char *input, t_shell *shell);
t_list	*input_to_tokens_lst(char *input, t_shell *shell);
char	*expand_token(char *token, t_list *env_vars);

// builtins
int		builtin_echo(t_cmd *cmd);
int		builtin_env(t_cmd *cmd, t_shell *shell);
int		builtin_cd(t_cmd *cmd, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, t_shell *shell);
int		builtin_unset(t_cmd *cmd, t_shell *shell);
int		builtin_exit(t_cmd *cmd, t_shell *shell);

// executor
void	executor(t_shell *shell);
int		default_exec(t_cmd *cmd, t_shell *shell);

// utils
int		count_splitted_2d(char **s_arr);
int		count_splitted_3d(char ***s_arr);
int		ft_strcmp(char *s1, char *s2);
char	**lststr_to_arr(t_list *lst);
void	print_error(char *cmd, char *error_msg);
void	print_env_var_val(int i, t_cmd *cmd, t_shell *shell);
int		ft_open_wronly_file(t_redir *redir);
int		ft_open_ronly_file(t_redir *redir);
void	free_array(char **array);

// Debug
void	debug_env_vars(t_list *head);
void	debug_print_parsed_info(t_shell *shell);
void	debug_quotes(char *input, t_shell *shell);

// Pipes
void	init_pipes(t_shell *shell);
void	dup_pipes_cmd(t_shell *shell, t_cmd *cmd, int i);
void	close_pipes_cmd(t_shell *shell, int i);
void	dup_pipes_out(t_shell *shell, t_cmd *cmd, int i);
void	dup_pipes_in(t_shell *shell, t_cmd *cmd, int i);

// Signals
void	handle_sig(int sig);
void	handle_sig_child(int sig);
void	handle_sig_ignore(int sig);
void	config_signal(t_sigaction *action, void (*handler)(int), int signum);

// Cleaner
int		free_shell_tmp(t_shell *shell);
int		free_tokens_arr(char ***tokens);
int		free_pipes(t_shell *shell);
int		free_cmds(t_shell *shell);
int		free_shell(t_shell *shell);
void	close_all_fds(void);

#endif
