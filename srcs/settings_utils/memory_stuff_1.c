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
		free_path_dir(data);
		free_env_table(data);
		if (data->aux)
			ft_lstclear(&data->aux, free);
		free(data);
	}
}
