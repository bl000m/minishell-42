/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:03:25 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/18 11:36:36 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// s == sending || r == receiving || p == parent
void	closing_input_output(t_minish *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}

void	free_path_dir(t_minish *data)
{
	int	i;

	i = 0;
	if (data->path_dir)
	{
		while (data->path_dir[i])
		{
			free(data->path_dir[i]);
			data->path_dir[i] = NULL;
			i++;
		}
		free(data->path_dir);
		data->path_dir = NULL;
	}
}

void	free_commands(t_minish *data)
{
	int	i;

	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
		{
			free(data->commands[i]);
			i++;
		}
		free(data->commands);
	}
}

void	exit_clean(t_minish *data)
{
	free_commands(data);
	free_path_dir(data);
	if (data->pipe[0])
		close(data->pipe[0]);
	if (data->pipe[1])
		close(data->pipe[1]);
	if (data->file_in)
		close(data->file_in);
	if (data->file_out)
		close(data->file_out);
	free(data);
}
