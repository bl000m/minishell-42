/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/19 18:06:23 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_envp(char *envp[])
{
	char	**dup;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(dup));
	if (!dup)
		return (NULL);
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]); // add an error management to free if needed.
	return (dup);
}

t_minish	*init_data(int argc)
{
	t_minish	*data;

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
	data->full_command = NULL;
	data->dir_command = NULL;
	data->child = 0;
	return (data);
}
