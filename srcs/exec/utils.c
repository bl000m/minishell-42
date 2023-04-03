/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:38:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 15:29:10 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switching_input_output(t_minish *data, t_cmd **cmd)
{
	(void) data;
	if ((*cmd)->input)
	{
		if (dup2((*cmd)->input, STDIN_FILENO) < 0)
			error_manager(0, EC_OUTPUTFD, (*cmd)->full_cmd[0], EXIT_FAILURE);
		close((*cmd)->input);
	}
	if ((*cmd)->output > 1)
	{
		if (dup2((*cmd)->output, STDOUT_FILENO) < 0)
			error_manager(0, EC_OUTPUTFD, (*cmd)->full_cmd[0], EXIT_FAILURE);
		close((*cmd)->output);
	}
	if ((*cmd)->file_in)
	{
		if (dup2((*cmd)->file_in, STDIN_FILENO) < 0)
			error_manager(0, EC_OUTPUTFD, (*cmd)->full_cmd[0], EXIT_FAILURE);
		close((*cmd)->file_in);
	}
	if ((*cmd)->file_out)
	{
		if (dup2((*cmd)->file_out, STDOUT_FILENO) < 0)
			error_manager(0, EC_OUTPUTFD, (*cmd)->full_cmd[0], EXIT_FAILURE);
		close((*cmd)->file_out);
	}
}

void	launching_command(t_minish *data, t_cmd **cmd)
{
	if (execve((*cmd)->full_path, (*cmd)->full_cmd, data->env_table) == -1)
		error_manager(127, EC_CMDNF, (*cmd)->full_cmd[0], 127);
}

void	closing_all_fd(t_minish *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (cmd->input)
			close(cmd->input);
		if (cmd->output > 1)
			close(cmd->output);
		cmd = cmd->next;
	}
}

void	closing_fd_if_redirections(t_minish *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (cmd->file_in && cmd->input)
			close(cmd->input);
		cmd = cmd->next;
	}
}

void	creating_pipes(t_minish *data)
{
	int		fd[2];
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
			error_manager(0, EC_PIPE, NULL, EXIT_FAILURE);
		cmd->output = fd[1];
		cmd->next->input = fd[0];
		cmd = cmd->next;
	}
	closing_fd_if_redirections(data);
}
