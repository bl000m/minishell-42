/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/09 13:38:39 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_input(t_minish *data)
{
	data->tokens = split_tokens(data);
	expand_path(data);
	parsing_path(data);
	creating_cmd_list(data);
}

char	**split_tokens(t_minish *data)
{
	char	**table;
	int		n_tokens;

	n_tokens = 0;
	if (!data->input)
		return (0);
	tokens_counter(data->input, &n_tokens);
	data->n_tokens = n_tokens;
	table = malloc(sizeof(char *) * (data->n_tokens + 1));
	if (!table)
		return (NULL);
	table = tokens_table_filling(data, table);
	if (table)
		table[data->n_tokens] = 0;
	return (table);
}

