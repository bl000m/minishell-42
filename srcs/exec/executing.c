/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/09 16:22:29 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executing_commands(t_minish *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	creating_pipes(data);
	while (cmd && cmd->full_cmd)
		cmd = creating_child(&cmd, data);
	closing_all_fd(data);
	cmd = data->cmds;
	while (cmd)
	{
		waitpid(data->child, NULL, 0);
		g_status = WEXITSTATUS(data->child);
		cmd = cmd->next;
	}
}

t_cmd	*creating_child(t_cmd **cmd, t_minish *data)
{
	int	pid;

	if (find_dir_command(data, (*cmd)->full_cmd[0])
		&& !ft_strncmp((*cmd)->full_cmd[0], "./", 2))
		error_manager(12, data, cmd);
	if (check_parent_builtin(cmd))
		executing_builtin(data, cmd);
	else
	{
		pid = fork();
		data->child = pid;
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

/* doubt: should we rename the builtins?*/
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

/* call tab_envp_updated(data) if (unset) || (export) in order
	to  recreate the env table if modified (after freeing the previous one)*/
void	executing_builtin(t_minish *data, t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		pwd(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		env(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5))
		unset(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "echo", 4))
		echo(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "export", 6))
		export(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "cd", 2))
		cd(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "exit", 4))
		mini_exit(cmd);
}
