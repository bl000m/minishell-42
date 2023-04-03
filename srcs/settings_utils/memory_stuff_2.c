/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:03:25 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 16:02:11 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	strs = NULL;
	return (0);
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

	ptr = data->cmds;
	while (ptr)
	{
		i = 0;
		while (ptr->full_cmd && ptr->full_cmd[i])
		{
			free(ptr->full_cmd[i]);
			ptr->full_cmd[i] = NULL;
			i++;
		}
		free(ptr->full_cmd);
		if (ptr->full_path)
			free(ptr->full_path);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	data->cmds = NULL;
}

void	free_tokens(t_minish *data)
{
	int	i;

	i = 0;
	if (data->tokens)
	{
		while (data->tokens[i])
		{
			if (data->tokens[i])
				free(data->tokens[i]);
			i++;
		}
		free(data->tokens);
		data->tokens = NULL;
	}
}
