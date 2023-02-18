/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:07:01 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/18 11:53:46 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*setting_prompt(void)
{
	char	*input;

    input = NULL;
	while (1)
	{
		input = readline("@minishell:~$ ");
        if (input && *input)
            add_history (input);
	}
    return (input);
}
