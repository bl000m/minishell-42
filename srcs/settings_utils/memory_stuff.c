/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:03:25 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/09 11:00:56 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_env_table(t_minish *data)
{
	int	i;

	i = 0;
	if (data->env_table)
	{
		while (data->env_table[i])
		{
			free(data->env_table[i]);
			data->env_table[i] = NULL;
			i++;
		}
		free(data->env_table);
		data->env_table = NULL;
	}
}

void	free_linked_list_full_cmd(t_minish *data)
{
	t_cmd	*tmp;
	t_cmd	*ptr;
	int		i;

	i = 0;
	ptr = data->cmds;
	while (ptr)
	{
		while (ptr->full_cmd && ptr->full_cmd[i])
		{
			free(ptr->full_cmd[i]);
			ptr->full_cmd[i] = NULL;
			i++;
		}
		free(ptr->full_cmd);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	free(ptr);
	ptr = NULL;
}

void	free_tokens(t_minish *data)
{
	int	i;

	i = 0;
	if (data->tokens)
	{
		while (data->tokens[i])
		{
			free(data->tokens[i]);
			i++;
		}
		free(data->tokens);
		data->tokens = NULL;
	}
}

void	exit_clean(t_minish *data)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		if (data->envp)
			dict_free(&data->envp);
		if (data->tokens)
			free_tokens(data);
		if (data->cmds)
			free_linked_list_full_cmd(data);
		free_path_dir(data);
		free_env_table(data);
		if (data->aux)
			ft_lstclear(&data->aux, free);
		free(data);
	}
}
