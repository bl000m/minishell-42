/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/24 15:14:22 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	updating_data(t_minish *data, char *prefix)
{
	free_path_dir(data);
	if (data->input)
		free(data->input);
	data->input = NULL;
	free(prefix);
	if (data->cmds)
		free_linked_list_full_cmd(data);
	if (data->tokens)
		free_tokens(data);
	init_cmd(data);
}

void	setting_prompt(t_minish *data)
{
	char	*prefix;

	set_signals(PROMPT);
	while (1)
	{
		prefix = get_lineprefix(data);
		data->input = readline(prefix);
		if (data->input && *data->input)
		{
			add_history (data->input);
			tab_envp_updated(data);
			if (!lexer_input(data))
			{
				// printf("g_status antes %d", g_status);
				executing_commands(data);
				// printf("g_status depois %d\n", g_status);
			}
		}
		if (data->input == NULL)
			break ;
		updating_data(data, prefix);
	}
	printf("exit\n");
}
