/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/06 16:20:21 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setting_prompt(t_minish *data)
{
	char	*prefix;

	// data->input = NULL;
	while (1)
	{
		init_data(data);
		prefix = get_lineprefix(data);
		data->input = readline(prefix);
		if (data->input && *data->input)
		{
			add_history (data->input);
			tab_envp_updated(data);
			lexer_input(data);
			executing_commands(data);
		}
		free(data->input);
		data->input = NULL;
		free(prefix);
		// exit_clean(data);
	}
}

