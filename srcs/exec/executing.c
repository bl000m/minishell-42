/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 15:14:50 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executing_commands(t_minish *data)
{
	t_cmd	*ptr;

	ptr = data->cmds;
	while (ptr)
	{
		creating_child(data, 2);
		if (data->child == 0)
			child_process(data, &ptr);
		switching_input_output(data, &ptr, 'i');
		ptr = ptr->next;
	}
	// close(data->pipe[0]);
	// close(data->pipe[1]);
	// closing_input_output(data, &data->cmds);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	child_process(t_minish *data, t_cmd **cmd)
{
	printf("cmd = %s\n", (*cmd)->full_cmd[0]);
	printf("input = %d\n", (*cmd)->input);
	printf("output = %d\n", (*cmd)->output);
	switching_input_output(data, cmd, 'i');
	switching_input_output(data, cmd, 'o');
	// close(data->pipe[0]);
	// close(data->pipe[1]);
	closing_input_output(data, cmd);
	if (check_builtin(cmd))
		executing_builtin(data, cmd);
	else
		launching_command(data, cmd);
}

int	check_builtin(t_cmd **cmd)
{
	return (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3)
		|| !ft_strncmp((*cmd)->full_cmd[0], "env", 3)
		|| (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5) 
		&&  (*cmd)->full_cmd[1]));
}

void	executing_builtin(t_minish *data, t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		pwd(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		env(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5) &&  (*cmd)->full_cmd[1])
		unset(data, (*cmd)->full_cmd[1]);

}