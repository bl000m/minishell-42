/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:38:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 15:12:16 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	switching_input_output(t_minish *data, t_cmd **cmd, char c)
{
	if (c == 'r')
	{
		if (dup2((*cmd)->input, STDIN_FILENO) < 0)
			error_manager(6, data, cmd);
	}
	else if (c == 's')
	{
		if (dup2((*cmd)->input, STDIN_FILENO) < 0)
			error_manager(6, data, cmd);
	}
	else if (c == 'e')
	{
		if (dup2((*cmd)->output, STDOUT_FILENO) < 0)
			error_manager(6, data, cmd);
	}
	else if (c == 'w')
	{
		if (dup2((*cmd)->output, STDOUT_FILENO) < 0)
			error_manager(6, data, cmd);
	}
}

void	launching_command(t_minish *data, t_cmd **cmd)
{
	// printf("%d", execve((*cmd)->full_path, (*cmd)->full_cmd, data->env_table) == -1);
	if (execve((*cmd)->full_path, (*cmd)->full_cmd, data->env_table) == -1)
		error_manager(3, data, cmd);
}

void	creating_pipe(t_minish *data)
{
	if (pipe(data->pipe) == -1)
		error_manager(1, data, NULL);
}

void	creating_child(t_minish *data, int err)
{
	data->child = fork();
	if (data->child == -1)
		error_manager(err, data, NULL);
}

// void	opening_files(t_minish *data, char *argv[], char flag)
// {
// 	if (flag == 'h')
// 	{
// 		data->file_out = open(argv[data->argc - 1], O_CREAT
// 				| O_WRONLY | O_APPEND, 0644);
// 		if (data->file_out == -1)
// 			error_manager(5, data);
// 	}
// 	else if (flag == 's')
// 	{
// 		data->file_in = open(argv[1], O_RDONLY);
// 		if (data->file_in == -1)
// 			ft_printf("INPUT ERROR: %s\n", strerror(errno));
// 		data->file_out = open(argv[data->argc - 1], O_CREAT
// 				| O_WRONLY | O_TRUNC, 0644);
// 		if (data->file_out == -1)
// 			error_manager(5, data);
// 	}
// }
