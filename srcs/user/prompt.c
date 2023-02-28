/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 12:40:43 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setting_prompt(t_minish *data)
{
    data->input = NULL;
	while (1)
	{
		data->input = readline("@minishell:~$ ");
        if (data->input && *data->input)
            add_history (data->input);
		tab_envp_updated(data);
		lexer_input(data);
		executing_commands(data);
		free(data->input);
		data->input = NULL;
		// exit_clean(data);
	}
}
