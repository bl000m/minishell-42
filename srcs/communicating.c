/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communicating_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 14:30:46 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	communicating(t_pipe *data, char *argv[], char *envp[])
{
	while (data->pos <= data->argc - 2)
	{
		creating_pipe(data);
		creating_child(data, 2);
		if (data->child == 0)
			child_process(data, argv, envp);
		switching_input_output(data, 'r');
		closing_input_output(data);
		data->pos++;
	}
	closing_input_output(data);
	close(data->file_out);
	exit_clean(data);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	child_process(t_pipe *data, char *argv[], char *envp[])
{
	matching_commands_with_right_path(data, argv, data->pos);
	if (data->pos == data->argc - 2)
		switching_input_output(data, 'e');
	else
		switching_input_output(data, 'w');
	closing_input_output(data);
	close(data->file_out);
	executing_command(data, envp);
}
