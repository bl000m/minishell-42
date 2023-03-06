/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/06 19:58:43 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrlc(int sign);

void	setting_prompt(t_minish *data, char **envp)
{
	char	*prefix;
	signal(SIGINT, handle_ctrlc);

	// data->input = NULL;
	while (1)
	{
		init_data(data, envp);
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
