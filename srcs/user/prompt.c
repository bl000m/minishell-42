/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/25 17:50:40 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* still to be free all (data->tokens etc) before starting over a new loop*/
void	setting_prompt(t_minish *data)
{
    data->full_command = NULL;
	while (1)
	{
		data->full_command = readline("@minishell:~$ ");
        if (data->full_command && *data->full_command)
            add_history (data->full_command);
		tab_envp_updated(data);
		lexer_full_command(data);
		// executing_commands(data);
		free(data->full_command);
		data->full_command = NULL;
	}
}
