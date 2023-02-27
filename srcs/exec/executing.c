/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 13:12:52 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executing_commands(t_minish *data)
{
	t_cmd	*ptr;

	ptr = data->cmds;
	// printf("cmd full cmd = %s\n", data->cmds->full_cmd[0]);
	// printf("cmd full path = %s\n", data->cmds->full_path);
	// printf("cmd input = %d\n", data->cmds->input);
	// printf("cmd output = %d\n", data->cmds->output);
	// printf("cmds_number(data) = %d\n", cmds_number(data));
	while (ptr)
	{
		if (cmds_number(data) != 1)
			creating_pipe(data);
		creating_child(data, 2);
		if (data->child == 0)
			child_process(data, &ptr);
		// if (cmds_number(data) != 1)
		// {
		// 	switching_input_output(data, 'r');
		// 	closing_input_output(data);
		// }
		ptr = ptr->next;
	}
	// closing_input_output(data);
	// close(data->file_out);
	// exit_clean(data);
	while (waitpid(-1, NULL, 0) > 0)
		;
}


void	child_process(t_minish *data, t_cmd **cmd)
{
	// if (data->pos == data->argc - 2)
	// 	switching_input_output(data, 'e');
	// else
		// switching_input_output(data, 'w');
	// closing_input_output(data);
	// close(data->file_out);
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		pwd(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		env(data, (*cmd)->output);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5) &&  (*cmd)->full_cmd[1])
		unset(data, (*cmd)->full_cmd[1]);
	else
		launching_command(data, cmd);
}
