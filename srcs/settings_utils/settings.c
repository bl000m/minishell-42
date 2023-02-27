/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 13:02:31 by mpagani          ###   ########.fr       */
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

char	**tab_envp_updated(t_minish *data)
{
	t_dict	*ptr;
	int		n_var;

	n_var = 0;
	data->env_table = malloc(sizeof(char *) * dict_size(data->envp) + 1);
	if (!data->envp)
		return (NULL);
	ptr = data->envp;
	while (ptr)
	{
		data->env_table[n_var] = ft_strjoin(ft_strjoin(ptr->key, "="), ptr->value);
		n_var++;
		ptr = ptr->next;
	}
	data->env_table[n_var] = 0;
	return (data->env_table);
}

static void	init_cmd(t_minish *data)
{
	t_cmd	*command;

	command = malloc(sizeof(*command));
	command->full_cmd = NULL;
	command->full_path = NULL;
	command->input = 0;
	command->output = 1;
	command->next = NULL;
	data->cmds = command;
}

static void	init_ptrs(t_minish *data, char *envp[])
{
	data->path = NULL;
	data->path_dir = NULL;
	// data->commands = NULL;
	data->input = NULL;
	data->dir_command = NULL;
	data->tokens = NULL;
	data->aux = NULL;
	data->env_table = NULL;
	data->envp = dup_envp(envp);
	data->env_table = NULL;
}

t_minish	*init_data(char *envp[])
{
	t_minish	*data;

	(void) envp;
	data = malloc(sizeof(*data));
	if (!data)
	{
		ft_printf("ERROR ALLOCATING DATA: %s\n", strerror(errno));
		exit(1);
	}
	data->pipe[1] = 0;
	data->pipe[0] = 0;
	data->n_cmd = 0;
	data->n_tokens = 0;
	data->child = 0;
	data->file_in = 0;
	data->file_out = 0;
	init_cmd(data);
	init_ptrs(data, envp);
	return (data);
}
