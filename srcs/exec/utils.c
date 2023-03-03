/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:38:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/02 12:37:30 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	switching_input_output(t_minish *data, t_cmd **cmd, char c)
{
	if (c == 'i')
	{
		if ((*cmd)->input)
		{
			if (dup2((*cmd)->input, STDIN_FILENO) < 0)
				error_manager(6, data, cmd);
		}
	}
	else if (c == 'o')
	{
		if ((*cmd)->output != 1)
		{
			if (dup2((*cmd)->output, STDOUT_FILENO) < 0)
				error_manager(6, data, cmd);
		}
	}
}

// before execve call the tab_envp_updated function
void	launching_command(t_minish *data, t_cmd **cmd)
{
	if (execve((*cmd)->full_path, (*cmd)->full_cmd, data->env_table) == -1)
		error_manager(3, data, cmd);
}

void	creating_pipes(t_minish *data)
{
	int		fd[2];
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmds->next != NULL)
	{
		if (pipe(fd) == -1)
			error_manager(1, data, NULL);
	cmd->outfile = fd[1];
	cmd->next->infile = fd[0];
	cmd = cmd->next;
	}
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
