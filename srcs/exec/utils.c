/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:38:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/31 15:31:36 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	switching_input_output(t_minish *data, t_cmd **cmd)
{
	if ((*cmd)->input)
	{
		if (dup2((*cmd)->input, STDIN_FILENO) < 0)
			error_manager(6, data, cmd);
		close((*cmd)->input);
	}
	if ((*cmd)->output > 1)
	{
		if (dup2((*cmd)->output, STDOUT_FILENO) < 0)
			error_manager(6, data, cmd);
		close((*cmd)->output);
	}
	if ((*cmd)->file_in)
	{
		if (dup2((*cmd)->file_in, STDIN_FILENO) < 0)
			error_manager(6, data, cmd);
		close((*cmd)->file_in);
	}
	if ((*cmd)->file_out)
	{
		if (dup2((*cmd)->file_out, STDOUT_FILENO) < 0)
			error_manager(6, data, cmd);
		close((*cmd)->file_out);
	}
}

void	launching_command(t_minish *data, t_cmd **cmd)
{
	if (execve((*cmd)->full_path, (*cmd)->full_cmd, data->env_table) == -1)
		error_manager(3, data, cmd);
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
			error_manager(1, data, NULL);
		cmd->output = fd[1];
		cmd->next->input = fd[0];
		if (!cmd->next->next)
			cmd->next->last = 1;
		cmd = cmd->next;
	}
	closing_fd_if_redirections(data);
}
