/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 12:02:21 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipe	*init_data(int argc)
{
	t_pipe	*data;

	data = malloc(sizeof(*data));
	if (!data)
	{
		ft_printf("ERROR ALLOCATING DATA: %s\n", strerror(errno));
		exit(1);
	}
	data->argc = argc;
	data->pipe[1] = 0;
	data->pipe[0] = 0;
	data->n_cmd = 0;
	data->pos = 0;
	data->file_in = 0;
	data->file_out = 0;
	data->path = NULL;
	data->path_dir = NULL;
	data->commands = NULL;
	data->dir_command = NULL;
	data->child = 0;
	return (data);
}
