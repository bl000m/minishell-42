/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/22 10:01:33 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    lexer_full_command(t_minish *data)
{
    data->tokens = split_tokens(data);
    expand_path(data);
    // split_redirect_pipes_tokens(data->tokens);
    print_out_tokens(data);
}

char    **split_tokens(t_minish *data)
{
    char	**table;
    int     n_tokens;

	n_tokens = 0;
	if (!data->full_command)
		return (0);
    tokens_counter(data->full_command, &n_tokens);
	data->n_tokens = n_tokens;
	table = malloc(sizeof(char *) * (data->n_tokens + 1));
	if (!table)
		return (NULL);
	table = tokens_table_filling(data, table);
	if (table)
		table[data->n_tokens] = 0;
	return (table);
}

//temporary
void	print_out_tokens(t_minish *data)
{
    int i;

    i = 0;
    while (i < data->n_tokens)
    {
        ft_printf("%s\n", data->tokens[i]);
        i++;
    }
}