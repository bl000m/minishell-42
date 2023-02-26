/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/25 17:30:28 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executing_commands(t_minish *data)
{
	// printf("cmd full cmd = %s\n", data->cmds->full_cmd[0]);
	// printf("cmd full path = %s\n", data->cmds->full_path);
	// printf("cmd input = %d\n", data->cmds->input);
	// printf("cmd output = %d\n", data->cmds->output);
	// printf("cmds_number(data) = %d\n", cmds_number(data));
	while (data->cmds)
	{
		if (cmds_number(data) != 1)
			creating_pipe(data);
		creating_child(data, 2);
		if (data->child == 0)
			child_process(data, &data->cmds);
		// if (cmds_number(data) != 1)
		// {
		// 	switching_input_output(data, 'r');
		// 	closing_input_output(data);
		// }
		data->cmds = data->cmds->next;
	}
	// closing_input_output(data);
	// close(data->file_out);
	exit_clean(data);
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
	launching_command(data, cmd);
}
