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
			free_env_table(data);
		if (data->path_dir)
			free_path_dir(data);
		if (data->aux)
			ft_lstclear(&data->aux, free);
		free(data);
	}
}

char	*mini_strdup(t_minish *data, char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (dup == NULL)
		hard_exit(data, NULL, NULL);
	return (dup);
}

char	*mini_join(t_minish *data, char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (joined == NULL)
		hard_exit(data, NULL, NULL);
	return (joined);
}
