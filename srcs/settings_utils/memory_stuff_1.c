/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:46:18 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 15:47:18 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (data->env_table)
			ft_free(data->env_table);
		if (data->path_dir)
			ft_free(data->path_dir);
		if (data->aux)
			ft_lstclear(&data->aux, free);
		free(data);
	}
}

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
		free(ptr->full_path);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	data->cmds = NULL;
}
