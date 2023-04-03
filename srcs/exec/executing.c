/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 16:26:30 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executing_commands(t_minish *data)
{
	t_cmd	*cmd;
	int		process_status;

	process_status = 0;
	cmd = data->cmds;
	if (!cmd->full_cmd)
		return ;
	creating_pipes(data);
	while (cmd && cmd->full_cmd)
		cmd = creating_child(&cmd, data);
	closing_all_fd(data);
	cmd = data->cmds;
	while (cmd)
	{
		waitpid(cmd->child, &process_status, 0);
		if (data->cmds && !check_parent_builtin(&cmd)
			&& !WIFSIGNALED(process_status))
			g_status = WEXITSTATUS(process_status);
		cmd = cmd->next;
	}
}

t_cmd	*creating_child(t_cmd **cmd, t_minish *data)
{
	int	pid;

	printf("command =>#%s#, output => %d, input => %d\n", (*cmd)->full_cmd[0], (*cmd)->output, (*cmd)->input);
	if (check_parent_builtin(cmd))
		executing_builtin(data, cmd);
	else
	{
		set_signals(EXEC);
		if (!ft_memcmp((*cmd)->full_cmd[0], "minishell", 10)
			|| !ft_memcmp((*cmd)->full_cmd[0], "./minishell", 12))
			set_signals(OFF);
		pid = fork();
		(*cmd)->child = pid;
		if (pid == -1)
		{
			closing_all_fd(data);
			error_manager(0, EC_PROCESS, NULL, EXIT_FAILURE);
		}
		else if (pid == 0)
			child_process(data, cmd);
	}
	return ((*cmd)->next);
}

void	child_process(t_minish *data, t_cmd **cmd)
{
	switching_input_output(data, cmd);
	closing_all_fd(data);
	if (check_child_builtin(cmd))
		executing_builtin(data, cmd);
	else
		launching_command(data, cmd);
}

int	check_child_builtin(t_cmd **cmd)
{
	return (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3)
		|| !ft_strncmp((*cmd)->full_cmd[0], "env", 3)
		|| !ft_strncmp((*cmd)->full_cmd[0], "echo", 4));
}

int	check_parent_builtin(t_cmd **cmd)
{
	return (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5)
		|| !ft_strncmp((*cmd)->full_cmd[0], "export", 6)
		|| !ft_strncmp((*cmd)->full_cmd[0], "cd", 2)
		|| !ft_strncmp((*cmd)->full_cmd[0], "exit", 4));
}
