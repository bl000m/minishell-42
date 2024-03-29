/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 15:29:21 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_envp(t_minish *data, t_dict **dict)
{
	t_dict	*ptr;
	char	*pwd;
	char	*tmpvar;

	pwd = getcwd(NULL, 0);
	ptr = dict_newnode("OLDPWD");
	if (!ptr)
		hard_exit(data, NULL, NULL);
	dict_addback(dict, ptr);
	tmpvar = ft_strjoin("PWD=", pwd);
	free(pwd);
	ptr = dict_newnode(tmpvar);
	free(tmpvar);
	if (!ptr)
		hard_exit(data, NULL, NULL);
	dict_addback(dict, ptr);
	ptr = dict_newnode("SHLVL=1");
	if (!ptr)
		hard_exit(data, NULL, NULL);
	dict_addback(dict, ptr);
	ptr = dict_newnode("_=~/Documents/minishell/./minishell");
	if (!ptr)
		hard_exit(data, NULL, NULL);
	dict_addback(dict, ptr);
}

/**
 * @brief
 * It will iterate over the array of arrays given in argument
 * and each time it will create a node with the key and value of the
 * variable.
 * That way it will return a linked list with all the variables.
 *
*/
static t_dict	*dup_envp(t_minish *data, char **envp)
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
			hard_exit(data, NULL, NULL);
		dict_addback(&dict, tmp);
	}
	if (!dict)
		generate_envp(data, &dict);
	else
		update_envp(data, dict);
	return (dict);
}

char	**tab_envp_updated(t_minish *data)
{
	t_dict	*ptr;
	int		n_var;
	char	*join;

	n_var = 0;
	if (data->env_table)
		free_env_table(data);
	data->env_table = ft_calloc(sizeof(char *), dict_size(data->envp) + 1);
	if (!data->envp)
		hard_exit(data, NULL, NULL);
	ptr = data->envp;
	while (ptr)
	{
		join = mini_join(data, ptr->key, "=");
		data->env_table[n_var] = mini_join(data, join, ptr->value);
		free(join);
		n_var++;
		ptr = ptr->next;
	}
	data->env_table[n_var] = NULL;
	return (data->env_table);
}

void	init_cmd(t_minish *data)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(*command), 1);
	command->full_cmd = NULL;
	command->full_path = NULL;
	command->next = NULL;
	command->input = 0;
	command->output = 1;
	command->file_in = 0;
	command->file_out = 0;
	command->child = 0;
	data->cmds = command;
}

void	init_ptrs(t_minish *data, char *envp[])
{
	data->path = NULL;
	data->path_dir = NULL;
	data->input = NULL;
	data->tokens = NULL;
	data->aux = NULL;
	data->env_table = NULL;
	data->envp = dup_envp(data, envp);
	data->env_table = NULL;
}
