/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/24 11:20:43 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief
 * It will iterate over the array of arrays given in argument
 * and each time it will create a node with the key and value of the
 * variable.
 * That way it will return a linked list with all the variables.
 *
 * OBS: add a function to deal with "env -i"
*/
static t_dict	*dup_envp(char **envp)
{
	t_dict	*dict;
	t_dict	*tmp;
	int		i;

	i = -1;
	dict = NULL;
	tmp = NULL;
	while (envp[++i])
	{
		tmp = dict_newnode(envp[i]);
		if (!tmp)
			return (NULL);
		dict_addback(&dict, tmp);
	}
	return (dict);
}

static void	init_ptrs(t_minish *data, char *envp[])
{
	data->path = NULL;
	data->path_dir = NULL;
	data->commands = NULL;
	data->cmds = NULL;
	data->full_command = NULL;
	data->dir_command = NULL;
	data->tokens = NULL;
	data->aux = NULL;
	data->completing_input = NULL;
	data->envp = dup_envp(envp);
}

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
	data->argc = argc;
	data->pipe[1] = 0;
	data->pipe[0] = 0;
	data->n_cmd = 0;
	data->n_tokens = 0;
	data->pos = 0;
	data->file_in = 0;
	data->file_out = 0;
	data->child = 0;
	init_ptrs(data, envp);
	return (data);
}
