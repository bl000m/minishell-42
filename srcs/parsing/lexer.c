/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:29 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/04 11:59:19 by mpagani          ###   ########.fr       */
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
	if (split_tokens(data))
		return (1);
	expand_path(data);
	parsing_path(data);
	res += creating_cmd_list(data);
	getting_rid_quotes_redirections_etc(data);
	return (res);
}

int	split_tokens(t_minish *data)
{
	int		n_tokens;
	int		res;

	n_tokens = 0;
	res = 0;
	if (!data->input)
		return (0);
	tokens_counter(data->input, &n_tokens);
	data->n_tokens = n_tokens;
	data->tokens = ft_calloc(sizeof(char *), (data->n_tokens + 1));
	if (!data->tokens)
		hard_exit(data, NULL, NULL);
	res = tokens_table_filling(data);
	if (data->tokens)
		data->tokens[data->n_tokens] = 0;
	return (res);
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
				tmp = getting_rid_of_quotes(data, curr->full_cmd[i]);
				free(curr->full_cmd[i]);
				curr->full_cmd[i] = tmp;
			}
			i++;
		}
		curr = curr->next;
	}
}

int	empty_token_handle(t_minish *data)
{
	if (!data->tokens[0][0])
	{
		error_manager(0, EC_CMDNF, data->tokens[0], EXIT_FAILURE);
		return (1);
	}
	return (0);
}
