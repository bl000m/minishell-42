/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/18 18:05:28 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    lexer_full_command(t_minish *data)
{
    split_spaces_quotes(data);
    // expanding_paths(data);
    // split_redirect_pipes_tokens(data->tokens);
}

void    split_spaces_quotes(t_minish *data)
{
    int i;

    i = 0;
    data->tokens = ft_strtok(data->full_command, " \'\"");
    // data->tokens = ft_split(data->full_command, ' ');
    while (data->tokens[i])
    {
        printf("%s\n", data->tokens[i]);
        i++;
    }
}

