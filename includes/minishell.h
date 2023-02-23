/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/23 14:35:45 by fbelfort         ###   ########.fr       */
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
	char			*key;
	size_t			key_len;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_minish
{
	int		argc;
	int		n_cmd;
	int		n_tokens;
	int		pos;
	int		file_in;
	int		file_out;
	char	*path;
	char	**path_dir;
	char	**tokens;
	char	*full_command;
	char	**commands;
	char	*dir_command;
	pid_t	child;
	int		pipe[2];
	t_list	*aux;
	t_dict	*envp;
}	t_minish;

/* builtins */

void		pwd(t_minish *data, int fd);

/* settings */

t_minish	*init_data(int argc, char *envp[]);
void		setting_prompt(t_minish *data);

/* lexical analysis */

void    	lexer_full_command(t_minish *data);
char    	**split_tokens(t_minish *data);

/* t_dict management */

t_dict		*dict_newnode(char *str);
void		dict_addback(t_dict **dict, t_dict *new);
size_t		dict_size(t_dict *dict);

/* parsing */

void		opening_files(t_minish *data, char *argv[], char flag);
void		parsing_environment(t_minish *data, char *envp[]);
char		*searching_path(char *envp[]);
char		*find_dir_command(t_minish *data);
void		expand_path(t_minish *data);
char		*find_varvalue(t_minish *data, char *variable, size_t len);

/* Bonus features */

int			checking_here_doc(int argc, char *argv[], t_minish *data);
void		here_doc(int argc, char *argv[], t_minish *data);
void		getting_and_writing_input_on_file(char *limiter, int fd);
void		multiple_commands_handling(int argc, char *argv[], t_minish *data);

/* communicating */

void		communicating(t_minish *data, char *argv[], char *envp[]);
void		creating_pipe(t_minish *data);
void		creating_child(t_minish *data, int err);
void		child_process(t_minish *data, char *argv[], char *envp[]);

/* utils */

void		matching_commands_with_right_path(t_minish *data, char *argv[], int pos);
void		switching_input_output(t_minish *data, char flag);
void		executing_command(t_minish *data, char *envp[]);
char		*duplicating_token(char *s, int start, int end);
char		**ft_free(char **strs);
int			are_quotes(char c);
void		print_out_tokens(t_minish *data);
void		pipe_redirections_handling(int *n_tokens);
void		pipe_redirections_token(int *start, int *end);

/* lexical analysis utils */

int			*tokens_counter(char *s, int *n_tokens);
char		**tokens_table_filling(t_minish *data, char **table);

/* error management */

void		error_manager(int error, t_minish *data);
void		check_error(int argc);

/* memory stuff */

void		closing_input_output(t_minish *data);
void		waiting_childs_finishing(t_minish *data);
void		free_path_dir(t_minish *data);
void		free_commands(t_minish *data);
void		exit_clean(t_minish *data);

#endif
