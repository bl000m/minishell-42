/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/31 09:38:14 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_path_line(t_minish *data);

int	lexer_input(t_minish *data)
{
	// int i;
	int	res;

	// i = 0;
	res = 0;
	data->tokens = split_tokens(data);
	// while (data->tokens[i])
	// {
	// 	printf("#%s#\n", data->tokens[i++]);
	// }
	expand_path(data);
	parsing_path(data);
	res = creating_cmd_list(data);
	return (res);
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
