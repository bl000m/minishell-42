/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/21 14:04:32 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* code the function that dup each line of envp and store the array
of string in struct*/
t_minish	*init_data(int argc, char *envp[])
{
	t_minish	*data;

	(void) envp;
	data = malloc(sizeof(*data));
	if (!data)
	{
		ft_printf("ERROR ALLOCATING DATA: %s\n", strerror(errno));
		exit(1);
	}
	// data->envp = NULL;
	data->argc = argc;
	data->pipe[1] = 0;
	data->pipe[0] = 0;
	data->n_cmd = 0;
	data->n_tokens = 0;
	data->pos = 0;
	data->file_in = 0;
	data->file_out = 0;
	data->path = NULL;
	data->path_dir = NULL;
	data->commands = NULL;
	data->full_command = NULL;
	data->dir_command = NULL;
	data->tokens = NULL;
	data->child = 0;
	return (data);
}
