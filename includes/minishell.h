/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/04 11:56:16 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>

extern int			g_status;

typedef struct s_dict
{
	size_t			key_len;
	size_t			has_value;
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	int				input;
	int				output;
	int				file_in;
	int				file_out;
	pid_t			child;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	char			*input;
	char			**tokens;
	t_cmd			*cmds;
	int				n_cmd;
	int				n_tokens;
	int				btw_double_quotes;
	int				btw_simple_quotes;
	int				start;
	int				end;
	char			*path;
	char			**path_dir;
	char			**env_table;
	t_dict			*envp;
	t_list			*aux;
}	t_minish;

/* signals */

void		set_signals(int caller);
void		handle_signal_prompt(int sign, siginfo_t *info, void *context);
void		handle_signal_exec(int sign);
void		handle_ctrlc_heredoc(int sign);

/* builtins */

void		mini_pwd(t_minish *data);
void		mini_unset(t_minish *data, t_cmd *cmd);
void		mini_env(t_minish *data, t_cmd *cmd);
void		print_sorted(t_minish *data, t_dict *envp);
void		mini_export(t_minish *data, t_cmd *cmd);
void		export_aux(t_minish *data, char *arg);
int			is_validvarname(char *varname, size_t len);
void		mini_echo(t_cmd *cmd);
void		mini_cd(t_minish *data, t_cmd *cmd);
void		mini_exit(t_minish *data, t_cmd **cmd);

/* settings */

t_minish	*init_data(char *envp[]);
void		setting_prompt(t_minish *data);
char		**tab_envp_updated(t_minish *data);
char		*get_lineprefix(t_minish *data);
void		update_envp(t_minish *data, t_dict *envp);
void		init_cmd(t_minish *data);
void		init_ptrs(t_minish *data, char *envp[]);

/* lexical analysis */

int			lexer_input(t_minish *data);
int			split_tokens(t_minish *data);

/* t_dict management */

t_dict		*dict_newnode(char *str);
void		dict_delone(t_dict **lst, t_dict *node);
void		dict_addback(t_dict **dict, t_dict *node);
size_t		dict_size(t_dict *dict);
t_dict		*dict_findvar(t_dict *envp, char *variable, size_t len);
t_dict		*dict_duplst(t_dict *dict);
int			set_varvalue(t_dict *envp, char *var, size_t len, char *newvalue);

/* parsing */

void		parsing_path(t_minish *data);
char		*find_dir_command(t_minish *data, char *command);
void		expand_path(t_minish *data);
char		*heredoc_expand(t_minish *data, char *line);
char		*make_line_fromlst(t_minish *data, t_list **lst);
char		*find_varvalue(t_minish *data, char *variable, size_t len);
int			creating_cmd_list(t_minish *data);
int			checking_token(t_minish *data, t_cmd **node, int *i);
int			stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i);
int			adding_full_path(t_minish *data, t_cmd **node);
void		generate_envp(t_minish *data, t_dict **dict);
int			specific_cases(t_minish *data, int *i, int *res);
void		duplicating_dollar(t_minish *data, char **token, char *s);
void		duplicating_with_conditions(t_minish *data, char **token, char *s);
void		simple_quotes_handling(t_minish *data, char *s);
void		double_quotes_handling(t_minish *data, char *s);
void		regroup_tokens(t_minish *data);
int			odd_quotes(char *s);
void		getting_rid_quotes_redirections_etc(t_minish *data);

/* parsing utils */

void		create_new_cmd_list_node(t_minish *data, t_cmd **node);
int			count_token_cmd(t_minish *data, int *i);
int			is_builtin(char *cmd);
int			input_redirection(t_minish *data, t_cmd **node, int *i);
int			output_redirection(t_minish *data, t_cmd **node, int *i);
int			output_append_redirection(t_minish *data, t_cmd **node, int *i);
int			pipe_new_node(t_minish *data, t_cmd **node, int *i);
int			cmds_number(t_minish *data);
int			heredoc_handling(t_minish *data, t_cmd **node, int *i);
char		*getting_rid_of_quotes(t_minish *data, char *token);
int			cmds_number(t_minish *data);
int			check_if_dollar(char *token);
void		realloc_data_tokens(t_minish *data, char **newtokens, int index);
void		split_expandedtoken(t_minish *data, int *index);
int			check_if_pipe_redirection(char *token);
int			empty_token_handle(t_minish *data);

/* Bonus features */

int			checking_here_doc(int argc, char *argv[], t_minish *data);
void		here_doc(t_minish *data, int *i, int fd, t_cmd **node);

/* executing */

void		executing_commands(t_minish *data);
void		creating_pipes(t_minish *data);
t_cmd		*creating_child(t_cmd **cmd, t_minish *data);
void		child_process(t_minish *data, t_cmd **cmd);
void		executing_builtin(t_minish *data, t_cmd **cmd);
int			check_child_builtin(t_cmd **cmd);
int			check_parent_builtin(t_cmd **cmd);

/* utils */

void		switching_input_output(t_minish *data, t_cmd **cmd);
void		launching_command(t_minish *data, t_cmd **cmd);
char		*duplicating_token(t_minish *data, char *s, int start, int end);
char		**ft_free(char **strs);
int			are_quotes(char c);
void		pipe_redirections_handling(char *s, int *n_tokens, int *i);
void		pipe_redirections_token(char *s, int *start, int *end);
void		closing_input_output(t_minish *data, t_cmd *cmd);
int			check_pipes(t_minish *data);
void		closing_all_fd(t_minish *data);

/* lexical analysis utils */

int			*tokens_counter(char *s, int *n_tokens);
int			tokens_table_filling(t_minish *data);

/* error management */

void		error_manager(int exit_code, char *message,
				void *var, int error_code);
void		check_error(int argc);
void		hard_exit(t_minish *data, char **tab, char *str);

/* memory stuff */

char		*mini_strdup(t_minish *data, char *str);
char		*mini_join(t_minish *data, char *s1, char *s2);
void		dict_free(t_dict **dict);
void		waiting_childs_finishing(t_minish *data);
void		free_path_dir(t_minish *data);
void		free_tokens(t_minish *data);
void		free_linked_list_full_cmd(t_minish *data);
void		exit_clean(t_minish *data);
void		free_env_table(t_minish *data);

/* MACROS FOR THE SIGNALS */

# define PROMPT 0
# define HEREDOC 1
# define EXEC 2
# define OFF 3

/* ERROR MESSAGES */

# define EC_PERMISSION "%s: Permission denied\n"
# define EC_PIPE "ERROR CREATING PIPE\n"
# define EC_PROCESS "ERROR CREATING PROCESS\n"
# define EC_CMDNF "command not found. %s\n"
# define EC_CMDNEXEC "command found but not executable. %s\n"
# define EC_CDNODIR "cd: No such file or directory\n"
# define EC_CDARG "cd: too many arguments\n"
# define EC_ENVARG "env: minishell should not manage arg for env\n"
# define EC_PATH "ENV PATH not set\n"
# define EC_PATH2 "ENV PATH not set. Cannot execute not built in functions\n"
# define EC_OUTPUT "OUTPUT ERROR: %s\n"
# define EC_INPUT "INPUT ERROR: %s\n"
# define EC_OUTPUTFD "ERROR in switching OUTPUT for %s fd\n"
# define EC_SINTAX "syntax error near unexpected token %s\n"
# define EC_SINTAX2 "syntax error near unexpected token\n"
# define EC_EXPORT "minishell: export: `%s': not a valid identifier\n"
# define EC_UNSET "minishell: unset: `%s': not a valid identifier \n"
# define EC_EXIT "exit: %s: numeric argument required\n"
# define EC_ODDQUOTES "An odd number of quotes is not allowed in Minishell.\n"
# define EC_PERIOD "minishell: .: filename argument required\n"
# define EC_PSLASH "minishell: ./: Is a directory\n"
# define EC_SLASH "minishell: /: Is a directory\n"
# define EC_HEREDOC "warning: document delimited by EOF (wanted `%s')\n> "

#endif
