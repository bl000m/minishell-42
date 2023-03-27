/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/27 15:51:27 by mpagani          ###   ########.fr       */
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

extern int	g_status;

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
	int				last;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	char	*input;
	char	**tokens;
	t_cmd	*cmds;
	int		n_cmd;
	int		n_tokens;
  	// int   	within_quotes;
	char	*path;
	char	**path_dir;
	char	**env_table;
	t_dict	*envp;
	pid_t	child;
	t_list	*aux;
}	t_minish;

/* signals */

void		set_signals(int caller);

/* builtins */

void		pwd(t_minish *data);
void		unset(t_minish *data, t_cmd *cmd);
void		env(t_minish *data, t_cmd *cmd);
void		print_sorted(t_dict *envp);
void		export(t_minish *data, t_cmd *cmd);
void		echo(t_cmd *cmd);
void		cd(t_minish *data, t_cmd *cmd);
void		mini_exit(t_cmd **cmd);

/* settings */

t_minish	*init_data(char *envp[]);
void		setting_prompt(t_minish *data);
char		**tab_envp_updated(t_minish *data);
char		*get_lineprefix(t_minish *data);
void		update_envp(t_dict *envp);
void		init_cmd(t_minish *data);

/* lexical analysis */

int			lexer_input(t_minish *data);
char		**split_tokens(t_minish *data);

/* t_dict management */

t_dict		*dict_newnode(char *str);
void		dict_delone(t_dict **lst, t_dict *node);
void		dict_addback(t_dict **dict, t_dict *new);
size_t		dict_size(t_dict *dict);
t_dict		*dict_findvar(t_dict *envp, char *variable, size_t len);
t_dict		*dict_duplst(t_dict *dict);
void		set_varvalue(t_dict *envp, char *var, size_t len, char *newvalue);

/* parsing */

void		parsing_path(t_minish *data);
char		*find_dir_command(t_minish *data, char *command);
void		expand_path(t_minish *data);
char		*make_line_fromlst(t_list **lst);
char		*find_varvalue(t_minish *data, char *variable, size_t len);
int			creating_cmd_list(t_minish *data);
int			checking_token(t_minish *data, t_cmd **node, int *i);
int			stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i);
int			adding_full_path(t_minish *data, t_cmd **node);
void		generate_envp(t_dict **dict);

/* parsing utils */

void		create_new_cmd_list_node(t_cmd **node);
int			count_token_cmd(t_minish *data, int *i);
int			is_builtin(char *cmd);
int			input_redirection(t_minish *data, t_cmd **node, int *i);
int			output_redirection(t_minish *data, t_cmd **node, int *i);
int			output_append_redirection(t_minish *data, t_cmd **node, int *i);
int			pipe_new_node(t_minish *data, t_cmd **node, int *i);
int			cmds_number(t_minish *data);
int			heredoc_handling(t_minish *data, t_cmd **node, int *i);
char		*getting_rid_of_quotes(char *token);

/* Bonus features */

int			checking_here_doc(int argc, char *argv[], t_minish *data);
void		here_doc(t_minish *data, int *i, int fd);

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
char		*duplicating_token(char *s, int start, int end);
char		**ft_free(char **strs);
int			are_quotes(char c);
void		pipe_redirections_handling(char *s, int *n_tokens, int *i);
void		pipe_redirections_token(char *s, int *start, int *end);
void		closing_input_output(t_minish *data, t_cmd *cmd);
int			check_pipes(t_minish *data);
void		closing_all_fd(t_minish *data);

/* lexical analysis utils */

int			*tokens_counter(char *s, int *n_tokens);
char		**tokens_table_filling(t_minish *data, char **table);

/* error management */

void		error_manager(int error, t_minish *data, t_cmd **cmd);
void		check_error(int argc);

/* memory stuff */

void		dict_free(t_dict **dict);
void		waiting_childs_finishing(t_minish *data);
void		free_path_dir(t_minish *data);
void		free_tokens(t_minish *data);
void		free_linked_list_full_cmd(t_minish *data);
void		exit_clean(t_minish *data);

# define PROMPT 0
# define HEREDOC 1
# define EXEC 2
# define NO_COLOR "\033[0m"
# define BLACK "\033[1;90m"
# define RED "\033[1;91m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"
# define BLUE "\033[1;94m"
# define PURPLE "\033[1;95m"
# define CYAN "\033[1;96m"
# define WHITE "\033[1;97m"

#endif
