/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 12:33:15 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updating_data(t_minish *data)
{
	if (data->path_dir)
		free_path_dir(data);
	if (data->input)
		free(data->input);
	data->input = NULL;
	if (data->cmds)
		free_linked_list_full_cmd(data);
	if (data->tokens)
		free_tokens(data);
	if (data->aux)
		ft_lstclear(&data->aux, free);
	data->btw_simple_quotes = 0;
	data->btw_double_quotes = 0;
	init_cmd(data);
}

void	setting_prompt(t_minish *data)
{
	char	*prefix;

	while (1)
	{
		set_signals(PROMPT);
		prefix = get_lineprefix(data);
		data->input = readline(prefix);
		free(prefix);
		if (data->input && *data->input)
		{
			add_history (data->input);
			tab_envp_updated(data);
			if (!lexer_input(data))
				executing_commands(data);
		}
		if (data->input == NULL)
			break ;
		updating_data(data);
	}
	printf("exit\n");
}
