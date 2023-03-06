/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/06 17:32:10 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executing_commands(t_minish *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	creating_pipes(data);
	while (cmd && cmd->full_cmd)
		cmd = creating_child(&cmd, data);
	exit_clean(data);
	closing_all_fd(data);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

t_cmd	*creating_child(t_cmd **cmd, t_minish *data)
{
	int	pid;

	// printf("cmd = %s, input= %d, output %d\n", (*cmd)->full_cmd[0], (*cmd)->input, (*cmd)->output);
	if (check_builtin(cmd))
	{
		switching_input_output(data, cmd);
		write(1, "coucou\n", 7);
		closing_all_fd(data);
		executing_builtin(data, cmd);
		// return ((*cmd)->next);
	}
	else
	{
		// printf("this is not a builtin\n");
		pid = fork();
		data->child = pid;
		if (pid == -1)
			error_manager(2, data, NULL);
		else if (pid == 0)
			child_process(data, cmd);
	}
	return ((*cmd)->next);
}

void	child_process(t_minish *data, t_cmd **cmd)
{
	// printf("we are in child\n");
	switching_input_output(data, cmd);
	closing_all_fd(data);
	launching_command(data, cmd);
}

/* doubt: should we rename the builtins?*/
int	check_builtin(t_cmd **cmd)
{
	return (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3)
		|| !ft_strncmp((*cmd)->full_cmd[0], "env", 3)
		|| !ft_strncmp((*cmd)->full_cmd[0], "echo", 4)
		|| !ft_strncmp((*cmd)->full_cmd[0], "unset", 5)
		|| !ft_strncmp((*cmd)->full_cmd[0], "export", 6)
		|| !ft_strncmp((*cmd)->full_cmd[0], "cd", 2));
}

/* call tab_envp_updated(data) if (unset) || (export) in order
	to  recreate the env table if modified (after freeing the previous one)*/

void	executing_builtin(t_minish *data, t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		pwd(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		env(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5))
		unset(data, (*cmd)->full_cmd[1]);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "export", 6))
		export(data, (*cmd)->output, (*cmd)->full_cmd[1]);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "echo", 4))
		echo((*cmd)->output, (*cmd)->full_cmd[1]);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "cd", 2))
		cd(data, (*cmd)->full_cmd[1]);

}
