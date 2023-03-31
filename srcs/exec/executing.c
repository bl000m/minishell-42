/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/31 15:30:52 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (data->cmds && !check_parent_builtin(&cmd))
			g_status = WEXITSTATUS(process_status);
		cmd = cmd->next;
	}
}

t_cmd	*creating_child(t_cmd **cmd, t_minish *data)
{
	int	pid;

	if (check_parent_builtin(cmd))
		executing_builtin(data, cmd);
	else
	{
		pid = fork();
		set_signals(EXEC);
		if (!ft_memcmp((*cmd)->full_cmd[0], "minishell", 10)
			|| !ft_memcmp((*cmd)->full_cmd[0], "./minishell", 10))
			set_signals(OFF);
		(*cmd)->child = pid;
		if (pid == -1)
		{
			closing_all_fd(data);
			error_manager(2, data, NULL);
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

void	executing_builtin(t_minish *data, t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		pwd(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		env(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5))
		unset(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "echo", 4))
		echo(*cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "export", 6))
		export(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "cd", 2))
		cd(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "exit", 4))
		mini_exit(cmd);
}
