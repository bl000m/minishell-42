/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 21:29:13 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updating_data(t_minish *data)
{
	if (data->path_dir)
		ft_free(data->path_dir);
	if (data->input)
		free(data->input);
	data->input = NULL;
	if (data->cmds)
		free_linked_list_full_cmd(data);
	if (data->tokens)
		ft_free(data->tokens);
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
