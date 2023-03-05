/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/03 16:46:27 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>

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
	char	*path;
	char	**path_dir;
	char	**env_table;
	t_dict	*envp;
	// int		pipe[2];
	pid_t	child;
	t_list	*aux;
}	t_minish;


/* builtins */

void		pwd(t_minish *data, int fd);
void		unset(t_minish *data, char *variable);
void		env(t_minish *data, int fd);
void		print_sorted(t_dict *envp, int fd);
void		export(t_minish *data, int fd, char *param);
void		echo(int fd, char *arg);
void		cd(t_minish *data, char *path);

/* settings */

void		init_data(t_minish *data, char *envp[]);
void		setting_prompt(t_minish *data, char **envp);
char		**tab_envp_updated(t_minish *data);
char		*get_lineprefix(t_minish *data);
void		update_envp(t_dict *envp);

/* lexical analysis */

void		lexer_input(t_minish *data);
char		**split_tokens(t_minish *data);

/* t_dict management */

t_dict		*dict_newnode(char *str);
void		dict_addback(t_dict **dict, t_dict *new);
size_t		dict_size(t_dict *dict);
t_dict		*dict_findvar(t_dict *envp, char *variable, size_t len);
t_dict		*dict_duplst(t_dict *dict);
void		dict_free(t_dict **dict);
void		set_varvalue(t_dict *envp, char *var, size_t len, char *newvalue);


/* parsing */

void		parsing_path(t_minish *data);
char		*find_dir_command(t_minish *data, char *command);
void		expand_path(t_minish *data);
char		*find_varvalue(t_minish *data, char *variable, size_t len);
void		creating_cmd_list(t_minish *data);
void		checking_token(t_minish *data, t_cmd **node, int *i);
void		stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i);
void		adding_full_path(t_minish *data, t_cmd **node);

/* parsing utils */
void		create_new_cmd_list_node(t_cmd **node);
int			count_token_cmd(t_minish *data, int *i);
int			is_builtin(char *cmd);
void		input_redirection(t_minish *data, t_cmd **node, int *i);
void		output_redirection(t_minish *data, t_cmd **node, int *i);
void		pipe_new_node(t_minish *data, t_cmd **node, int *i);
int			cmds_number(t_minish *data);
void		heredoc_handling(t_minish *data, t_cmd **node, int *i);

/* Bonus features */

int			checking_here_doc(int argc, char *argv[], t_minish *data);
void		here_doc(t_minish *data, t_cmd **node, int *i);
void		getting_and_writing_input_on_pipe(char *limiter, int fd);

/* executing */

void		executing_commands(t_minish *data);
void		creating_pipes(t_minish *data);
t_cmd		*creating_child(t_cmd **cmd, t_minish *data);
void		child_process(t_minish *data, t_cmd **cmd);
void		executing_builtin(t_minish *data, t_cmd **cmd);
int			check_builtin(t_cmd **cmd);

/* utils */

void		switching_input_output(t_minish *data, t_cmd **cmd);
void		launching_command(t_minish *data, t_cmd **cmd);
char		*duplicating_token(char *s, int start, int end);
char		**ft_free(char **strs);
int			are_quotes(char c);
void		pipe_redirections_handling(int *n_tokens);
void		pipe_redirections_token(int *start, int *end);
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

void		waiting_childs_finishing(t_minish *data);
void		free_path_dir(t_minish *data);
void		free_tokens(t_minish *data);
void		exit_clean(t_minish *data);

#endif
