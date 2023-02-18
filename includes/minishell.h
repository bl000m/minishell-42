/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/18 11:47:37 by mpagani          ###   ########.fr       */
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

typedef struct s_minish
{
	int		argc;
	int		n_cmd;
	int		pos;
	int		file_in;
	int		file_out;
	char	*path;
	char	**path_dir;
	char	*full_command;
	char	**commands;
	char	*dir_command;
	pid_t	child;
	int		pipe[2];
}	t_minish;

/* settings */
t_minish	*init_data(int argc);
char		*setting_prompt(void);

/* parsing */
void		opening_files(t_minish *data, char *argv[], char flag);
void		parsing_environment(t_minish *data, char *envp[]);
char		*searching_path(char *envp[]);
char		*find_dir_command(t_minish *data);

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