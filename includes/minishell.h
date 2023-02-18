/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 14:29:29 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "errno.h"
# include "string.h"

typedef struct s_pipe
{
	int		argc;
	int		n_cmd;
	int		pos;
	int		file_in;
	int		file_out;
	char	*path;
	char	**path_dir;
	char	**commands;
	char	*dir_command;
	pid_t	child;
	int		pipe[2];
}	t_pipe;

/* settings */
t_pipe	*init_data(int argc);

/* parsing */
void	opening_files(t_pipe *data, char *argv[], char flag);
void	parsing_environment(t_pipe *data, char *envp[]);
char	*searching_path(char *envp[]);
char	*find_dir_command(t_pipe *data);

/* Bonus features */
int		checking_here_doc(int argc, char *argv[], t_pipe *data);
void	here_doc(int argc, char *argv[], t_pipe *data);
void	getting_and_writing_input_on_file(char *limiter, int fd);
void	multiple_commands_handling(int argc, char *argv[], t_pipe *data);

/* communicating */
void	communicating(t_pipe *data, char *argv[], char *envp[]);
void	creating_pipe(t_pipe *data);
void	creating_child(t_pipe *data, int err);
void	child_process(t_pipe *data, char *argv[], char *envp[]);

/* utils */
void	matching_commands_with_right_path(t_pipe *data, char *argv[], int pos);
void	switching_input_output(t_pipe *data, char flag);
void	executing_command(t_pipe *data, char *envp[]);

/* error management */
void	error_manager(int error, t_pipe *data);
void	check_error(int argc);

/* memory stuff */
void	closing_input_output(t_pipe *data);
void	waiting_childs_finishing(t_pipe *data);
void	free_path_dir(t_pipe *data);
void	free_commands(t_pipe *data);
void	exit_clean(t_pipe *data);

#endif
