/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/02 12:24:27 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	generate_envp(t_dict **dict)
{
	t_dict	*ptr;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ptr = dict_newnode("OLDPWD");
	if (!ptr)
		return ;
	dict_addback(dict, ptr);
	ptr = dict_newnode(ft_strjoin("PWD=", pwd));
	free(pwd);
	if (!ptr)
		return ;
	dict_addback(dict, ptr);
	ptr = dict_newnode("SHLVL=1");
	if (!ptr)
		return ;
	dict_addback(dict, ptr);
	ptr = dict_newnode("_=~/Documents/minishell/./minishell");
	if (!ptr)
		return ;
	dict_addback(dict, ptr);
}

/**
 * @brief
 * It will iterate over the array of arrays given in argument
 * and each time it will create a node with the key and value of the
 * variable.
 * That way it will return a linked list with all the variables.
 *
 * OBS: descobrir o que eh o '_' e ajustar o SHLVL
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
	if (!dict)
		generate_envp(&dict);
	else
		update_envp(dict);
	return (dict);
}

char	**tab_envp_updated(t_minish *data)
{
	t_dict	*ptr;
	int		n_var;
	char	*join;

	n_var = 0;
	data->env_table = malloc(sizeof(char *) * (dict_size(data->envp) + 1));
	if (!data->envp)
		return (NULL);
	ptr = data->envp;
	while (ptr)
	{
		join = ft_strjoin(ptr->key, "=");
		data->env_table[n_var] = ft_strjoin(join, ptr->value);
		free(join);
		n_var++;
		ptr = ptr->next;
	}
	data->env_table[n_var] = NULL;
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
	data->input = NULL;
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

void	update_envp(t_dict *envp)
{
	int		lvl;
	t_dict	*ptr;

	set_varvalue(envp, "SHELL", 5, "minishell");
	ptr = dict_findvar(envp, "SHLVL", 5);
	lvl = ft_atoi(ptr->value) + 1;
	free(ptr->value);
	ptr->value = ft_itoa(lvl);
}
