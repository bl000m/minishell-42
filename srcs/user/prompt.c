/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/07 21:44:08 by FelipeBelfo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_ctrlc(int sign);

void	updating_data(t_minish *data, char *prefix)
{
	free_path_dir(data);
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

	signal(SIGQUIT, handle_ctrlc);
	signal(SIGINT, handle_ctrlc);
	signal(EOF, handle_ctrlc);

	while (1)
	{
		prefix = get_lineprefix(data);
		data->input = readline(prefix);
		if (data->input && *data->input)
		{
			add_history (data->input);
			tab_envp_updated(data);
			lexer_input(data);
			executing_commands(data);
		}
		updating_data(data, prefix);
	}
}
