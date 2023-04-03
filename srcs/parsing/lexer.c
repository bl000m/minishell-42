/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 16:09:56 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_input(t_minish *data)
{
	int		res;

	res = 0;
	if (odd_quotes(data->input))
	{
		error_manager(0, EC_ODDQUOTES, NULL, EXIT_FAILURE);
		return (1);
	}
	data->tokens = split_tokens(data);
	expand_path(data);
	parsing_path(data);
	res += creating_cmd_list(data);
	getting_rid_quotes_redirections_etc(data);
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

void	getting_rid_quotes_redirections_etc(t_minish *data)
{
	int		i;
	char	*tmp;
	t_cmd	*curr;

	curr = data->cmds;
	tmp = NULL;
	while (curr)
	{
		i = 0;
		while (curr->full_cmd && curr->full_cmd[i])
		{
			if (check_if_pipe_redirection(curr->full_cmd[i]))
			{
				tmp = getting_rid_of_quotes(curr->full_cmd[i]);
				free(curr->full_cmd[i]);
				curr->full_cmd[i] = tmp;
			}
			i++;
		}
		curr = curr->next;
	}
}
